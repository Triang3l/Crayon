add_executable(CrayonSketch)
target_include_directories(CrayonSketch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_sources(CrayonSketch
  PRIVATE
    x64/Start.asm)
