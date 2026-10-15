# Test dla struktury Event
#add_executable(test_event test_Event.cpp)
#target_link_libraries(test_event PRIVATE mood_tracker_lib)
#add_test(NAME TestEvent COMMAND test_event)

# Test dla klasy MoodTracker
add_executable(test_mood_tracker test_MoodTracker.cpp)
target_link_libraries(test_mood_tracker PRIVATE mood_tracker_lib)
add_test(NAME TestMoodTracker COMMAND test_mood_tracker)