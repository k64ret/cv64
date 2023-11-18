set(IDO_DOWNLOAD_VERSION "latest")
# or pin a specific version - e.g. `set(IDO_DOWNLOAD_VERSION "v0.6")`

if(WIN32)
  set(IDO_DETECTED_OS "windows")
elseif(APPLE)
  set(IDO_DETECTED_OS "macos")
else(#[[ UNIX ]]
)
  set(IDO_DETECTED_OS "linux")
endif()

string(
  CONCAT IDO_5_3_DOWNLOAD_URL
         "https://github.com" # GitHub
         "/decompals/ido-static-recomp" # repository
         "/releases/${IDO_DOWNLOAD_VERSION}" # release version
         "/download/ido-5.3-recomp-${IDO_DETECTED_OS}.tar.gz" # artifact
)
string(
  CONCAT IDO_7_1_DOWNLOAD_URL
         "https://github.com" # GitHub
         "/decompals/ido-static-recomp" # repository
         "/releases/${IDO_DOWNLOAD_VERSION}" # release version
         "/download/ido-7.1-recomp-${IDO_DETECTED_OS}.tar.gz" # artifact
)

set(IDO_DOWNLOAD_URLS ${IDO_5_3_DOWNLOAD_URL} ${IDO_7_1_DOWNLOAD_URL})

set(IDO_5_3_DOWNLOAD_LOCATION "tools/ido/ido-5.3-recomp-${IDO_DETECTED_OS}.tar.gz")
set(IDO_7_1_DOWNLOAD_LOCATION "tools/ido/ido-7.1-recomp-${IDO_DETECTED_OS}.tar.gz")

set(IDO_DOWNLOAD_LOCATIONS ${IDO_5_3_DOWNLOAD_LOCATION} ${IDO_7_1_DOWNLOAD_LOCATION})

set(IDO_5_3_EXTRACT_LOCATION "tools/ido/${IDO_DETECTED_OS}/5.3/")
set(IDO_7_1_EXTRACT_LOCATION "tools/ido/${IDO_DETECTED_OS}/7.1/")

set(IDO_EXTRACT_LOCATIONS ${IDO_5_3_EXTRACT_LOCATION} ${IDO_7_1_EXTRACT_LOCATION})

# Downloads prebuilt IDO 5.3/7.1 binaries for your OS
function(download_ido_release_artifact url to)
  message(STATUS "Downloading ${url}")
  file(DOWNLOAD ${url} ${to})
endfunction()

# Extracts IDO binaries from the containing archive
function(extract_ido_archive archive destination)
  message(STATUS "Extracting ${archive} to ${destination}")
  # cmake-lint: disable=E1126
  file(
    ARCHIVE_EXTRACT
    INPUT
    ${archive}
    DESTINATION
    ${destination})
endfunction()

# Make IDO 5.3/7.1 binaries available for use in main build
function(download_and_extract_ido)
  foreach(
    url
    location
    destination
    IN
    ZIP_LISTS
    IDO_DOWNLOAD_URLS
    IDO_DOWNLOAD_LOCATIONS
    IDO_EXTRACT_LOCATIONS)
    download_ido_release_artifact(${url} ${location})
    extract_ido_archive(${location} ${destination})
  endforeach()
  file(REMOVE ${IDO_DOWNLOAD_LOCATIONS})
endfunction()

download_and_extract_ido()
