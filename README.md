# Base Module for MTA:SA
## Developing
1. Download and install the EditorConfig plugin for Visual Studio: [https://github.com/editorconfig/editorconfig-visualstudio#readme](https://github.com/editorconfig/editorconfig-visualstudio#readme)
2. Launch `premake.bat`
3. Open `Build/NAME.sln`
### Debugging
1. Create a directory junktion to MTA-Server directory in the root of the repo
    * `mklink /J mta-server "PATH_TO_INSTALL_DIR\MTA San Andreas 1.5\server"`
2. Create a symlink to the build output dll in the modules directory
    * `cd PATH_TO_INSTALL_DIR\MTA San Andreas 1.5\server\x64\modules` for x64
    * `cd PATH_TO_INSTALL_DIR\MTA San Andreas 1.5\server\mods\deathmatch\modules` for Win32
    * `mklink ml_sysutils.dll "PATH_TO_REPO\Bin\Debug\ml_sysutils.dll"`
3. Press `F5` in Visual Studio and the MTA-Server should start

## Installing
1. Put the resulting `Bin/ml_sysutils.dll/.so` into your MTA:SA server `modules` folder.
2. Add `<module src="ml_sysutils.dll"/>` (or `.so` for Linux) to your `mtaserver.conf`.
3. Start the server

## API
### Globals

### Functions

## Download
via https://github.com/Contextualist/glare
* [Linux x64](https://glare.now.sh/eXo-OpenSource/ml_sysutils/ml_sysutils.so)
* [Windows x64](https://glare.now.sh/eXo-OpenSource/ml_sysutils/ml_sysutils_x64.dll)
* [Windows x86](https://glare.now.sh/eXo-OpenSource/ml_sysutils/ml_sysutils_win32.dll)

## Contributors
* Jusonex
* Stefan K.
