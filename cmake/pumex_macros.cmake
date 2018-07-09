SET(CMAKE_DEBUG_POSTFIX "d")
SET(CMAKE_RELEASE_POSTFIX "")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
SET(CMAKE_MINSIZEREL_POSTFIX "s")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

MACRO(set_executable_postfixes target)
  set_target_properties(${target} PROPERTIES DEBUG_OUTPUT_NAME "${target}${CMAKE_DEBUG_POSTFIX}")
  set_target_properties(${target} PROPERTIES RELEASE_OUTPUT_NAME "${target}${CMAKE_RELEASE_POSTFIX}")
  set_target_properties(${target} PROPERTIES RELWITHDEBINFO_OUTPUT_NAME "${target}${CMAKE_RELWITHDEBINFO_POSTFIX}")
  set_target_properties(${target} PROPERTIES MINSIZEREL_OUTPUT_NAME "${target}${CMAKE_MINSIZEREL_POSTFIX}")
ENDMACRO(set_executable_postfixes)

function( process_shaders INPUT_DIR INPUT_SHADER_NAMES SHADERS_IN SHADERS_OUT )
  set ( RESULT_IN )
  set ( RESULT_OUT )
  foreach( _file ${${INPUT_SHADER_NAMES}})
    set( _file_in  "${INPUT_DIR}/${_file}" )
    set( _file_out "${CMAKE_BINARY_DIR}/${_file}.spv" )
    add_custom_command (OUTPUT  ${_file_out}
                        DEPENDS ${_file_in}
                        COMMAND glslangValidator
                        ARGS    -V ${_file_in} -o ${_file_out} )
    list (APPEND RESULT_IN  ${_file_in} )
    list (APPEND RESULT_OUT ${_file_out} )
  endforeach(_file)
  set( ${SHADERS_IN}  "${RESULT_IN}"  PARENT_SCOPE )
  set( ${SHADERS_OUT} "${RESULT_OUT}" PARENT_SCOPE )
endfunction(process_shaders)

