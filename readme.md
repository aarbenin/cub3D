
# cub3D 🎪🔪🤡

Welcome to **cub3D**, a 3D maze exploration game inspired by classic titles like Wolfenstein 3D. Built using the **Ray-Casting** technique, this project offers a first-person perspective of a maze, rendered using **minilibX-linux**. The game simulates the experience of navigating through a maze with the ability to open doors, view a minimap, and use different controls for movement and interaction.

![Screenshot of cub3D](./img/screen.gif)

### Features
- **Realistic 3D Maze**: Navigate through a maze in a first-person view.
- **Wall Textures**: Dynamic textures for walls, depending on the direction (North, South, East, West).
- **Doors**: Open and close doors in the maze.
- **Minimap**: A real-time minimap that displays the player's location and field of view.
- **Animations and Sprites**: Custom animations and interactive sprites in the game.
- **Mouse & Keyboard Controls**: Rotate and move the player using both mouse and keyboard.

### Controls
- **W, A, S, D**: Move around the maze.
- **Arrow Keys or Mouse**: Rotate the player's view.
- **E**: Open/close doors.
- **Spacebar**: Pause and resume the game.
- **ESC or Q**: Quit the game.

### Installation and Execution
To compile the game, run:
```bash
make
```

To run the game, provide the path to a `.cub` map file as an argument:
```bash
./cub3D ./maps/1_main.cub
```

### Requirements
- The game was developed using **minilibX-linux** and can be played only on linux.

---

### 🛠️ **Development Highlights** 🛠️
The game was built using **minilibX-linux** and **Ray-Casting** techniques. Key challenges included perfecting the collision detection for doors and walls, ensuring smooth movement, and adding a live minimap that tracks the player’s position and field of view. To give players more immersion, we added mouse control for looking around and a bit of fun with some hidden mechanics in the game (hint: don’t mess with doors!). 

---

### 🎪 **The Maze Creators** 🎪

- [**Alisa Arbenina**](https://github.com/aarbenin)
- [**Oleg Goman**](https://github.com/OleGoman85)
