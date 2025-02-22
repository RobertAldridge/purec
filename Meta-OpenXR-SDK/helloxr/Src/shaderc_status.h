
// shaderc_status.h

// Indicate the status of a compilation.
enum shaderc_compilation_status
{
 shaderc_compilation_status_success = 0,
 shaderc_compilation_status_invalid_stage = 1, // error stage deduction
 shaderc_compilation_status_compilation_error = 2,
 shaderc_compilation_status_internal_error = 3, // unexpected failure
 shaderc_compilation_status_null_result_object = 4,
 shaderc_compilation_status_invalid_assembly = 5,
 shaderc_compilation_status_validation_error = 6,
 shaderc_compilation_status_transformation_error = 7,
 shaderc_compilation_status_configuration_error = 8,
};
