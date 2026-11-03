add_executable(service-restart-tracker-test
    service_restart_tracker_test.cpp)

target_include_directories(service-restart-tracker-test PRIVATE
    ${PROJECT_SOURCE_DIR}/frame)

add_test(NAME service-restart-tracker
    COMMAND service-restart-tracker-test)
