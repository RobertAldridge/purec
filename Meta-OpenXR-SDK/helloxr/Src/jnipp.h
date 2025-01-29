
// jnipp.h

struct JNIEnv_;
struct _JNIEnv;
struct JavaVM_;
struct _JavaVM;
struct _jmethodID;
struct _jfieldID;
class _jobject;
class _jclass;
class _jarray;

namespace jni
{
  typedef _JNIEnv JNIEnv;
  typedef _JavaVM JavaVM;

  typedef _jobject* jobject;
  typedef _jclass* jclass;
  typedef _jarray* jarray;

  typedef _jmethodID* method_t;

  typedef _jfieldID* field_t;

  typedef unsigned char byte_t;

#ifdef JNIPP_EXCEPTION_CLASS

  typedef JNIPP_EXCEPTION_CLASS Exception;

#else

  typedef std::runtime_error Exception;

#endif // JNIPP_EXCEPTION_CLASS

  class Object;
  template <class TElement> class Array;

  namespace internal
  {
    inline std::string valueSig(const void*) { return "V"; }
    inline std::string valueSig(const bool*) { return "Z"; }
    inline std::string valueSig(const byte_t*) { return "B"; }
    inline std::string valueSig(const wchar_t*) { return "C"; }
    inline std::string valueSig(const short*) { return "S"; }
    inline std::string valueSig(const int*) { return "I"; }
    inline std::string valueSig(const long long*) { return "J"; }
    inline std::string valueSig(const float*) { return "F"; }
    inline std::string valueSig(const double*) { return "D"; }
    inline std::string valueSig(const std::string*) { return "Ljava/lang/String;"; }
    inline std::string valueSig(const std::wstring*) { return "Ljava/lang/String;"; }
    inline std::string valueSig(const char* const*) { return "Ljava/lang/String;"; }
    inline std::string valueSig(const wchar_t* const*) { return "Ljava/lang/String;"; }
    std::string valueSig(const Object* obj);
    inline std::string valueSig(const Object* const* obj) { return valueSig(obj ? *obj : nullptr); }

    template <class TArg> inline std::string valueSig(const Array<TArg>*) { return "[" + valueSig( (TArg*) nullptr); }

    template <int n, class TArg> inline std::string valueSig(const TArg(*arg)[n] ) { return valueSig( (const TArg* const*)arg); }

    inline std::string sig() { return ""; }

    template <class TArg, class... TArgs> std::string sig(const TArg& arg, const TArgs&... args)
    {
      return valueSig(&arg) + sig(args...);
    }

    typedef long long value_t;

    void valueArg(value_t* v, bool a);
    void valueArg(value_t* v, byte_t a);
    void valueArg(value_t* v, wchar_t a);
    void valueArg(value_t* v, short a);
    void valueArg(value_t* v, int a);
    void valueArg(value_t* v, long long a);
    void valueArg(value_t* v, float a);
    void valueArg(value_t* v, double a);
    void valueArg(value_t* v, jobject a);
    void valueArg(value_t* v, const Object& a);
    void valueArg(value_t* v, const Object* const& a);
    void valueArg(value_t* v, const std::string& a);
    void valueArg(value_t* v, const char* a);
    void valueArg(value_t* v, const std::wstring& a);
    void valueArg(value_t* v, const wchar_t* a);
    void valueArg(value_t* v, std::nullptr_t);

    inline void args(value_t*) {}

    template <class TArg, class... TArgs> void args(value_t* values, const TArg& arg, const TArgs&... args)
    {
      valueArg(values, arg);
      internal::args(values + 1, args...);
    }

    template <class TArg> void cleanupArg(value_t* /* value */) {}
    template <> void cleanupArg<std::string>(value_t* value);
    template <> void cleanupArg<std::wstring>(value_t* value);
    template <> void cleanupArg<const char*>(value_t* value);
    template <> void cleanupArg<const wchar_t*>(value_t* value);

    template <class TArg = void, class... TArgs> void cleanupArgs(value_t* values)
    {
      cleanupArg<TArg>(values);
      cleanupArgs<TArgs...>(values + 1);
    }

    template <> inline void cleanupArgs<void>(value_t* /* values */) {}

    template <class... TArgs> class ArgArray
    {
public:

      ArgArray(const TArgs&... args)
      {
        std::memset(this, 0, sizeof(ArgArray<TArgs...>) );
        internal::args(values, args...);
      }

      ~ArgArray()
      {
        cleanupArgs<TArgs...>(values);
      }

      value_t values[sizeof...(TArgs)];
    };

    template <> class ArgArray<>
    {
public:

      ArgArray()
      {
        std::memset(this, 0, sizeof(ArgArray<>) );
      }

      ~ArgArray()
      {
      }

      value_t values[1];
    };

    long getArrayLength(jarray array);

    template<typename T> struct ReturnTypeWrapper
    {
      using type = T;
    };
  }

  void init(JNIEnv* env);

  void init(JavaVM* vm);

  JNIEnv* env();

  class Object
  {
public:

    enum ScopeFlags
    {
      Temporary = 1,
      DeleteLocalInput = 2
    };

    Object() noexcept;

    Object(const Object& other);

    Object(Object&& other) noexcept;

    Object(jobject ref, int scopeFlags = 0);

    virtual ~Object() noexcept;

    Object& operator=(const Object& other);

    Object& operator=(Object&& other);

    bool operator==(const Object& other) const;

    bool operator!=(const Object& other) const { return !operator==(other); }

    template <class TReturn> TReturn call(method_t method) const { return callMethod(method, nullptr, internal::ReturnTypeWrapper<TReturn> {} ); }

    template <class TReturn> TReturn call(const char* name) const
    {
      if(std::strstr(name, "()") )
        return call<TReturn>(getMethod(name) );

      method_t method = getMethod(name, ("()" + internal::valueSig( (TReturn*) nullptr) ).c_str() );
      return call<TReturn>(method);
    }

    template <class TReturn, class... TArgs> TReturn call(method_t method, const TArgs&... args) const
    {
      internal::ArgArray<TArgs...> transform(args...);
      return callMethod(method, transform.values, internal::ReturnTypeWrapper<TReturn> {} );
    }

    template <class TReturn, class... TArgs> TReturn call(const char* name, const TArgs&... args) const
    {
      if(std::strchr(name, '(') )
        return call<TReturn>(getMethod(name), args...);

      std::string sig = "(" + internal::sig(args...) + ")" + internal::valueSig( (TReturn*) nullptr);
      method_t method = getMethod(name, sig.c_str() );
      return call<TReturn>(method, args...);
    }

    template <class TType> TType get(field_t field) const
    {
      return getFieldValue(field, internal::ReturnTypeWrapper<TType> {} );
    }

    template <class TType> TType get(const char* name) const
    {
      field_t field = getField(name, internal::valueSig( (TType*) nullptr).c_str() );
      return get<TType>(field);
    }

    template <class TType> void set(field_t field, const TType& value);

    template <class TType> void set(const char* name, const TType& value)
    {
      field_t field = getField(name, internal::valueSig( (TType*) nullptr).c_str() );
      set(field, value);
    }

    bool isNull() const noexcept;

    jclass getClass() const;

    jobject getHandle() const noexcept { return _handle; }

    jobject makeLocalReference() const;

private:

    method_t getMethod(const char* name, const char* signature) const;
    method_t getMethod(const char* nameAndSignature) const;
    field_t getField(const char* name, const char* signature) const;

    void callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<void> const&) const;
    bool callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<bool> const&) const;
    byte_t callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<byte_t> const&) const;
    wchar_t callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<wchar_t> const&) const;
    short callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<short> const&) const;
    int callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<int> const&) const;
    long long callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<long long> const&) const;
    float callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<float> const&) const;
    double callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<double> const&) const;
    std::string callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<std::string> const&) const;
    std::wstring callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<std::wstring> const&) const;
    jni::Object callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<jni::Object> const&) const;
    jarray callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<jarray> const&) const;

    template<typename T> jni::Array<T> callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<jni::Array<T>> const&) const;

    void getFieldValue(field_t field, internal::ReturnTypeWrapper<void> const&) const;
    bool getFieldValue(field_t field, internal::ReturnTypeWrapper<bool> const&) const;
    byte_t getFieldValue(field_t field, internal::ReturnTypeWrapper<byte_t> const&) const;
    wchar_t getFieldValue(field_t field, internal::ReturnTypeWrapper<wchar_t> const&) const;
    short getFieldValue(field_t field, internal::ReturnTypeWrapper<short> const&) const;
    int getFieldValue(field_t field, internal::ReturnTypeWrapper<int> const&) const;
    long long getFieldValue(field_t field, internal::ReturnTypeWrapper<long long> const&) const;
    float getFieldValue(field_t field, internal::ReturnTypeWrapper<float> const&) const;
    double getFieldValue(field_t field, internal::ReturnTypeWrapper<double> const&) const;
    std::string getFieldValue(field_t field, internal::ReturnTypeWrapper<std::string> const&) const;
    std::wstring getFieldValue(field_t field, internal::ReturnTypeWrapper<std::wstring> const&) const;
    jni::Object getFieldValue(field_t field, internal::ReturnTypeWrapper<jni::Object> const&) const;

    jobject _handle;
    mutable jclass _class;
    bool _isGlobal;
  };

  class Class : protected Object
  {
public:

    Class() : Object() {}

    Class(const char* name);

    Class(jclass ref, int scopeFlags = Temporary);

    bool isNull() const noexcept { return Object::isNull(); }

    Object newInstance() const;

    template <class... TArgs> Object newInstance(method_t constructor, const TArgs&... args) const
    {
      internal::ArgArray<TArgs...> transform(args...);
      return newObject(constructor, transform.values);
    }

    template <class... TArgs> Object newInstance(const TArgs&... args) const
    {
      method_t constructor = getMethod("<init>", ("(" + internal::sig(args...) + ")V").c_str() );
      return newInstance(constructor, args...);
    }

    field_t getField(const char* name, const char* signature) const;

    template<typename TType> field_t getField(const char* name) const
    {
      return getField(name, internal::valueSig( (TType*) nullptr).c_str() );
    }

    field_t getStaticField(const char* name, const char* signature) const;

    template<typename TType> field_t getStaticField(const char* name) const
    {
      return getStaticField(name, internal::valueSig( (TType*)nullptr).c_str() );
    }

    method_t getMethod(const char* name, const char* signature) const;

    method_t getMethod(const char* nameAndSignature) const;

    method_t getStaticMethod(const char* name, const char* signature) const;

    method_t getStaticMethod(const char* nameAndSignature) const;

    method_t getConstructor(const char* signature) const { return getMethod("<init>", signature); }

    Class getParent() const;

    std::string getName() const;

    template <class TReturn> TReturn call(method_t method) const { return callStaticMethod<TReturn>(method, nullptr); }

    template <class TReturn> TReturn call(const char* name) const
    {
      method_t method = getStaticMethod(name, ("()" + internal::valueSig( (TReturn*) nullptr) ).c_str() );
      return call<TReturn>(method);
    }

    template <class TReturn, class... TArgs> TReturn call(method_t method, const TArgs&... args) const
    {
      internal::ArgArray<TArgs...> transform(args...);
      return callStaticMethod<TReturn>(method, transform.values);
    }

    template <class TReturn, class... TArgs> TReturn call(const char* name, const TArgs&... args) const
    {
      if(std::strchr(name, '(') )
        return call<TReturn>(getStaticMethod(name), args...);

      std::string sig = "(" + internal::sig(args...) + ")" + internal::valueSig( (TReturn*) nullptr);
      method_t method = getStaticMethod(name, sig.c_str() );
      return call<TReturn>(method, args...);
    }

    template <class TReturn> TReturn call(const Object& obj, method_t method) const
    {
      return callExactMethod<TReturn>(obj.getHandle(), method, nullptr);
    }

    template <class TReturn> TReturn call(const Object& obj, const char* name) const
    {
      method_t method = getMethod(name, ("()" + internal::valueSig( (TReturn*) nullptr) ).c_str() );
      return call<TReturn>(obj, method);
    }

    template <class TReturn> TReturn call(const Object* obj, const char* name) const
    {
      return call<TReturn>(obj, name);
    }

    template <class TReturn, class... TArgs> TReturn call(const Object& obj, method_t method, const TArgs&... args) const
    {
      internal::ArgArray<TArgs...> transform(args...);
      return callExactMethod<TReturn>(obj.getHandle(), method, transform.values);
    }

    template <class TReturn, class... TArgs> TReturn call(const Object* obj, method_t method, const TArgs&... args) const
    {
      return call<TReturn>(*obj, method, args...);
    }

    template <class TReturn, class... TArgs> TReturn call(const Object& obj, const char* name, const TArgs&... args) const
    {
      std::string sig = "(" + internal::sig(args...) + ")" + internal::valueSig( (TReturn*) nullptr);
      method_t method = getMethod(name, sig.c_str() );
      return call<TReturn>(obj, method, args...);
    }

    template <class TReturn, class... TArgs> TReturn call(const Object* obj, const char* name, const TArgs&... args) const
    {
      return call<TReturn>(*obj, name, args...);
    }

    template <class TType> TType get(field_t field) const;

    template <class TType> TType get(const char* name) const
    {
      field_t field = getStaticField(name, internal::valueSig( (TType*) nullptr).c_str() );
      return get<TType>(field);
    }

    template <class TType> void set(field_t field, const TType& value);

    template <class TType> void set(const char* name, const TType& value)
    {
      field_t field = getStaticField(name, internal::valueSig( (TType*) nullptr).c_str() );
      set(field, value);
    }

    jclass getHandle() const noexcept { return jclass(Object::getHandle() ); }

private:

    template <class TType> TType callStaticMethod(method_t method, internal::value_t* values) const;
    template <class TType> TType callExactMethod(jobject obj, method_t method, internal::value_t* values) const;
    Object newObject(method_t constructor, internal::value_t* args) const;
  };

  class Enum : protected Class
  {
public:

    Enum(const char* name);

    Object get(const char* name) const;

private:

    std::string _name;
  };

  template <class TElement> class Array : public Object
  {
public:

    Array() noexcept;

    Array(jarray ref, int scopeFlags = Temporary);

    Array(long length);

    Array(long length, const Class& type);

    Array(const Array<TElement>& other);

    Array(Array<TElement>&& other) noexcept;

    Array<TElement>& operator=(const Array<TElement>& other);

    Array<TElement>& operator=(Array<TElement>&& other);

    bool operator==(const Array<TElement>& other) const { return Object::operator==(other); }

    bool operator!=(const Array<TElement>& other) const { return !operator==(other); }

    void setElement(long index, TElement value);

    TElement getElement(long index) const;
    TElement operator[](long index) const { return getElement(index); }

    long getLength() const;

    jarray getHandle() const noexcept { return jarray(Object::getHandle() ); }

private:

    mutable long _length;
  };

  class Vm final
  {
public:

    Vm(const char* path = nullptr);

    ~Vm();
  };

  class InvocationException : public Exception
  {
public:

    InvocationException(const char* msg = "Java Exception detected") : Exception(msg) {}
  };

  class NameResolutionException : public Exception
  {
public:

    NameResolutionException(const char* name) : Exception(name) {}
  };

  class InitializationException : public Exception
  {
public:

    InitializationException(const char* msg) : Exception(msg) {}
  };

  template <typename T> inline jni::Array<T> Object::callMethod(method_t method, internal::value_t* args, internal::ReturnTypeWrapper<jni::Array<T> > const& ) const
  {
    jarray result = callMethod(method, args, internal::ReturnTypeWrapper<jarray> {} );

    return jni::Array<T>(result, DeleteLocalInput);
  }

  template <class TElement> Array<TElement>::Array() noexcept : Object(), _length(0)
  {
  }

  template <class TElement> Array<TElement>::Array(jarray ref, int scopeFlags) : Object( (jobject) ref, scopeFlags), _length(-1)
  {
  }

  template <class TElement> Array<TElement>::Array(const Array<TElement>& other) : Object(other), _length(other._length)
  {
  }

  template <class TElement> Array<TElement>::Array(Array<TElement>&& other) noexcept : Object( (Object&&)other), _length(other._length)
  {
    other._length = 0;
  }

  template <class TElement> Array<TElement>& Array<TElement>::operator=(const Array<TElement>& other)
  {
    if(&other != this)
    {
      Object::operator=(other);
      _length = other._length;
    }

    return *this;
  }

  template <class TElement> Array<TElement>& Array<TElement>::operator=(Array<TElement>&& other)
  {
    if(&other != this)
    {
      Object::operator=( (Object&&) other);
      _length = other._length;

      other._length = 0;
    }

    return *this;
  }

  template <class TElement> long Array<TElement>::getLength() const
  {
    if(_length < 0)
    {
      _length = internal::getArrayLength(getHandle() );
    }

    return _length;
  }
}
