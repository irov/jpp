macro(ADD_MOVIE_TEST testname)
    IF(WIN32)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    ENDIF()
    
    ADD_EXECUTABLE(test_${testname} test_${testname}.cpp example.json)
    
    TARGET_LINK_LIBRARIES(test_${testname} jpp jansson)

    set_target_properties (test_${testname} PROPERTIES
        FOLDER tests
    )

    ADD_TEST(NAME ${testname} COMMAND ./test_${testname} ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

ADD_MOVIE_TEST(load)