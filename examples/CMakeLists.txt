function(add_example name)
  add_executable(${name} ${name}.cxx)
  target_link_libraries(${name}
    maybe_ptr
  )
endfunction()

add_example(hierarchy)
add_example(basic_example)
add_example(ownerize)
add_example(unique_covariant)
