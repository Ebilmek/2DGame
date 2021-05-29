set(supported_extensions ".jpg;.png")
#to add more...
#list(APPEND supported_extensions "txt")

file(GLOB_RECURSE project_asset_files 
    LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/*[${supported_extensions}]"
)
# Basically the same as global as the one above is the root, CACHE INTERNAL "" instead of PARENT_SCOPE would do a similar thing here, just not stored in the cache
set(PROJECT_ASSET_FILES ${project_asset_files} PARENT_SCOPE)
set(SUPPORTED_EXTENSIONS ${supported_extensions} PARENT_SCOPE)

# --log-level VERBOSE in command line recommended
#set(CMAKE_MESSAGE_LOG_LEVEL VERBOSE)
message(VERBOSE "Supported extensions: ${supported_extensions}")
message(VERBOSE "Found asset files: ")
foreach(asset_file_name ${project_asset_files})
    message(VERBOSE "${asset_file_name}")
endforeach()