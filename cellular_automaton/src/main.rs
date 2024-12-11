use rand::Rng;
use minifb::{Key, Window, WindowOptions};

const CELL_SIZE: usize = 10; // Taille d'une cellule en pixels

#[derive(Clone, Copy)]
pub struct Cell {
    current_state: bool,
    next_state: bool,
}

impl Cell {
    pub fn new(state: bool) -> Self {
        Self {
            current_state: state,
            next_state: false,
        }
    }

    pub fn is_alive(&self) -> bool {
        self.current_state
    }

    pub fn set_next_state(&mut self, state: bool) {
        self.next_state = state;
    }

    pub fn update_state(&mut self) {
        self.current_state = self.next_state;
    }
}

pub struct Grid {
    rows: usize,
    cols: usize,
    cells: Vec<Cell>,
}

impl Grid {
    pub fn new(rows: usize, cols: usize) -> Self {
        let mut rng = rand::thread_rng();
        let cells = (0..rows * cols)
            .map(|_| Cell::new(rng.gen_bool(0.5)))
            .collect();

        Self { rows, cols, cells }
    }

    pub fn get_cell(&self, row: isize, col: isize) -> Option<&Cell> {
        if row < 0 || col < 0 || row >= self.rows as isize || col >= self.cols as isize {
            return None;
        }
        let index = (row as usize) * self.cols + (col as usize);
        self.cells.get(index)
    }

    pub fn get_cell_mut(&mut self, row: isize, col: isize) -> Option<&mut Cell> {
        if row < 0 || col < 0 || row >= self.rows as isize || col >= self.cols as isize {
            return None;
        }
        let index = (row as usize) * self.cols + (col as usize);
        self.cells.get_mut(index)
    }

    pub fn count_alive_neighbors(&self, row: usize, col: usize) -> usize {
        let directions = [
            (-1, -1),
            (-1, 0),
            (-1, 1),
            (0, -1),
            (0, 1),
            (1, -1),
            (1, 0),
            (1, 1),
        ];
        directions
            .iter()
            .filter_map(|(dx, dy)| self.get_cell(row as isize + dx, col as isize + dy))
            .filter(|cell| cell.is_alive())
            .count()
    }

    pub fn update_all_cells(&mut self) {
        for cell in &mut self.cells {
            cell.update_state();
        }
    }

    pub fn render(&self, buffer: &mut Vec<u32>) {
        for row in 0..self.rows {
            for col in 0..self.cols {
                let color = if self.cells[row * self.cols + col].is_alive() {
                    0xFFFFFF // Blanc pour les cellules vivantes
                } else {
                    0x000000 // Noir pour les cellules mortes
                };

                for y in 0..CELL_SIZE {
                    for x in 0..CELL_SIZE {
                        let index = (row * CELL_SIZE + y) * self.cols * CELL_SIZE + (col * CELL_SIZE + x);
                        buffer[index] = color;
                    }
                }
            }
        }
    }
}

pub struct Automaton {
    grid: Grid,
}

impl Automaton {
    pub fn new(rows: usize, cols: usize) -> Self {
        Self {
            grid: Grid::new(rows, cols),
        }
    }

    pub fn apply_rules(&mut self) {
        let rows = self.grid.rows;
        let cols = self.grid.cols;

        for row in 0..rows {
            for col in 0..cols {
                let alive_neighbors = self.grid.count_alive_neighbors(row, col);
                if let Some(cell) = self.grid.get_cell_mut(row as isize, col as isize) {
                    if cell.is_alive() {
                        cell.set_next_state(alive_neighbors == 2 || alive_neighbors == 3);
                    } else {
                        cell.set_next_state(alive_neighbors == 3);
                    }
                }
            }
        }
        self.grid.update_all_cells();
    }

    pub fn run_simulation(&mut self) {
        let width = self.grid.cols * CELL_SIZE;
        let height = self.grid.rows * CELL_SIZE;
        let mut window = Window::new(
            "Cellular Automaton",
            width,
            height,
            WindowOptions::default(),
        )
        .unwrap_or_else(|e| panic!("Unable to open window: {}", e));

        let mut buffer: Vec<u32> = vec![0; width * height];

        while window.is_open() && !window.is_key_down(Key::Escape) {
            self.grid.render(&mut buffer);
            window.update_with_buffer(&buffer, width, height).unwrap();
            self.apply_rules();
        }
    }
}

fn main() {
    let mut automaton = Automaton::new(100, 200); // Grille 50x50
    automaton.run_simulation(); // Lancer la simulation interactive
}
