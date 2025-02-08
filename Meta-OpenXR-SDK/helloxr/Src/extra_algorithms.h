
// extra_algorithms.h

template <typename T, typename Pred> static inline void map_erase_if(T& container, Pred&& predicate)
{
  for(auto it = container.begin(); it != container.end(); )
  {
    if(predicate(*it) )
      it = container.erase(it);
    else
      ++it;
  }
}

template <typename T, typename Alloc, typename Pred> static inline void vector_remove_if_and_erase(
  std::vector<T, Alloc>& vec,
  Pred&& predicate
)
{
  auto b = vec.begin();
  auto e = vec.end();

  vec.erase(std::remove_if(b, e, std::forward<Pred>(predicate) ), e);
}
