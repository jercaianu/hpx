# Copyright (c) 2007-2014 Hartmut Kaiser
# Copyright (c)      2014 Thomas Heller
# Copyright (c) 2011-2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(tests
  enable
)
set(enable_PARAMETERS LOCALITIES 2)
set(enable_PARAMETERS THREADS_PER_LOCALITY 4)

foreach(test ${tests})
  set(sources
      ${test}.cpp)

  source_group("Source Files" FILES ${sources})

  # add example executable
  add_hpx_executable(${test}_test
                     SOURCES ${sources}
                     ${${test}_FLAGS}
                     FOLDER "Tests/Unit/LCOs")

  add_hpx_unit_test("parcelset" ${test} ${${test}_PARAMETERS})

  # add a custom target for this example
  add_hpx_pseudo_target(tests.unit.parcelset.${test})

  # make pseudo-targets depend on master pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.parcelset
                              tests.unit.parcelset.${test})

  # add dependencies to pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.parcelset.${test}
                              ${test}_test_exe)
endforeach()
