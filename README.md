# DOS experiments

Each experiment lives in its own directory. To build a single-file C program:

1. Open this repository in VS Code and open the experiment's `.c` file.
2. Press F5.
3. Check the terminal for compiler output. The `.exe` and intermediate files
   are written next to the source file. F5 builds only; it does not run the program.

F5 is configured in your VS Code user keyboard shortcuts for C files under
`C:\dev\DOS\dos-stuff`. If you move the repository or use another machine,
update or recreate that shortcut, or use Ctrl+Shift+B instead.

The build requires Open Watcom installed at `C:\WATCOM`, including
`binnt64\wcl.exe`. The task uses the active file, so keep
that file selected when starting the build. Ctrl+Shift+B also runs the build.
For experiments with multiple source files or different build options, add an
appropriate separate build task.
