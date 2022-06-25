add_library(labs)

target_sources(labs
  PRIVATE
        lab3/repository/FSRepository.cpp
        lab3/repository/MockRepository.cpp
        lab3/restorepoint/AbstractFSRestorePoint.cpp
        lab3/restorepoint/AbstractRestorePoint.cpp
        lab3/restorepoint/ZipSingleFileRestorePoint.cpp
        lab3/restorepoint/ZipSplitFileRestorePoint.cpp
        lab3/restorepoint/MockRestorePoint.cpp
        lab3/storage/FileStorage.cpp
        lab3/storage/MemoryStorage.cpp
        lab3/util/backupjob/BackupJob.cpp
        lab3/util/backupjob/FileJobObject.cpp
        lab3/util/backupjob/MockJobObject.cpp
  PUBLIC
        lab3/repository/IRepository.h
        lab3/repository/FSRepository.h
        lab3/repository/MockRepository.h
        lab3/restorepoint/AbstractFSRestorePoint.h
        lab3/restorepoint/AbstractRestorePoint.h
        lab3/restorepoint/IRestorePoint.h
        lab3/restorepoint/ZipSingleFileRestorePoint.h
        lab3/restorepoint/ZipSplitFileRestorePoint.h
        lab3/restorepoint/MockRestorePoint.h
        lab3/storage/FileStorage.h
        lab3/storage/IStorage.h
        lab3/storage/MemoryStorage.h
        lab3/util/backupjob/BackupJob.h
        lab3/util/backupjob/IJobObject.h
        lab3/util/backupjob/FileJobObject.h
        lab3/util/backupjob/MockJobObject.h
        lab3/util/factory/RepositoryFactory.h
        lab3/util/factory/RestorePointFactory.h
        lab3/util/factory/StorageFactory.h
        lab3/util/factory/enums/StorageType.h
        lab3/util/factory/enums/RestorePointType.h
        lab3/util/factory/enums/RepositoryType.h
  )

target_link_libraries(labs PUBLIC zipios)

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(labs
    PUBLIC
      "--coverage"
    )
  target_link_options(labs
    INTERFACE
      "--coverage"
    )
endif()
