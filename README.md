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

## Note on AI use
In an attempt to maximimise learning, all the code in this repo is hand written, with as little AI assistance as possible.

I am trying to get as much information as I can out of the book PC Intern, but when I have questions (which is often) I have used AI as a source of knowlege.



