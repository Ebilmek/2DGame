
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Assets)
# Add in all files but txt, although should be using all supported extensions, couldn't find a decent way to do it
# TODO: Spend more time here, find a way how to incorporate a list foreach doesn't seem to work

file(COPY ${CMAKE_CURRENT_LIST_DIR}/../Assets 
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR} 
        FILES_MATCHING 
        PATTERN "gear.png"
        PATTERN "ball.jpg"
        PATTERN "CMakeLists.txt" EXCLUDE
        #EXTENSIONS_TO_ITER(${SUPPORTED_EXTENSIONS})
) # [${SUPPORTED_EXTENSIONS}]


#[[macro(EXTENSIONS_TO_ITER extensions_to_be_iterated)
    foreach(extension IN LISTS ${extensions_to_be_iterated})
        PATTERN "*${extension}"
    endforeach()
endmacro()]]
