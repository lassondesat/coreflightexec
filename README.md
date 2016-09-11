# NASA Core Flight Executive (cFE)

[![GitHub release](https://img.shields.io/github/release/yusend/coreflightexec.svg)](https://github.com/yusend/coreflightexec/releases)

## Description

"The Core Flight Executive is a portable, platform independent embedded
system framework developed by NASA Goddard Space Flight Center. This
framework is used as the basis for the flight software for satellite data
systems and instruments, but can be used on other embedded systems."
-- http://sourceforge.net/projects/coreflightexec/

Additional documentation can be found in:
* [cfe-OSS-readme.txt](./cfe-OSS-readme.txt)
* [docs](./docs/)
* [cfe/docs](./cfe/docs/)

## Requirements
* [Git LFS](https://git-lfs.github.com/). Details [here](https://github.com/github/git-lfs/wiki/Tutorial).

## Setup

1. Install [Git](https://www.git-scm.com/downloads) and [Git LFS](https://github.com/github/git-lfs/wiki/Installation)
2. Clone this project:

   ```bash
   git clone --recursive https://github.com/yusend/coreflightexec.git
   cd coreflightexec
   git lfs install
   git lfs pull
   ```

  Make sure that the setup has completed successfully, by checking that the
  `osal` directory is non-empty (contains files and folders). Also check that
  the files listed in `.gitattributes` at the end file under the "Define large
  file storage (LFS) support" are present in their entirety (not text file
  placeholders).

## Sources
* http://opensource.gsfc.nasa.gov/projects/cfe/index.php
* http://sourceforge.net/projects/coreflightexec/ (cFE-6.5.0a-OSS-release.tar.gz)

## Dependecies
* https://github.com/nasa/osal

## License
* [SUA_Open_Source_cFE 6 1_GSC-16232.pdf](SUA_Open_Source_cFE 6 1_GSC-16232.pdf)
