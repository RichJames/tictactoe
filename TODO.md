TO DO:

- I've introduced a bug in the computer move logic. Fix that.
- Restructure main game loop logic to break out the loop for one game from the larger program loop. So that it can be tested,
- Restructure project with top directory and src, build, tests, etc. subdirectories
- Change saved games approach to use order of moves (e.g. 13526 - cell 1, then 3, then 5... First one is always X. Odds are X, evens are O)
- Have AI avoid making losing moves
- Run tidy-clang again and fix issues found
- Run cppcheck against code.
- Build a web front-end
- Redo database interface via RESTful API
- Set up and test interacting with a Postgres database.
- Add debug and release build switches to makefile
- Consider if refactoring to use a design pattern is warranted
