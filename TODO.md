TO DO:

- Restructure main game loop logic to break out the loop for one game from the larger program loop. So that it can be tested.
- Redo database interface via RESTful API
- Build a web front-end
- Restructure Board class to remove game logic. It should be a reusable grid that could potentially be used for many games. In fact, I could generalize it to an N x M grid.
- Move game logic to a new class: TTTGame.
  - Judge if moves are legal
  - Determine if there is a winner or a draw
  - Orchestrate player play order
- Change saved games approach to use order of moves (e.g. 13526 - cell 1, then 3, then 5... First one is always X. Odds are X, evens are O)
- Have AI avoid making losing moves
- Run tidy-clang again and fix issues found
- Run cppcheck against code.
- Set up and test interacting with a Postgres database.
- Add debug and release build switches to makefile
- Consider if refactoring to use a design pattern is warranted
