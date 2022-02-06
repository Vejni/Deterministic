# Deterministic optimisation

This repo contains code to solve Deterministic Optimisation assignment in the Optimization course of the UAB master's in Modelling for Science and Engineering. The repo structure is as follows:

- docs: Contains the problem statement, and report about the project.
- logs: Contains the output files.
- src: Contains the source code.
- plot: Script for plotting and outputs.

Main executable: main

Arguments (in order):

| **Parameter** | **Functionality**                                                          | **Range**    | **Default**               |
|---------------|----------------------------------------------------------------------------|--------------|---------------------------|
| mode          | Selects the optimiser, i.e gradient descent (1) vs conjugate gradient (0). | 0, 1         | 1                         |
| x             | Starting $x$ coordinate.                                                   | $\mathbb{R}$ | -1.5                      |
| y             | Starting $y$ coordinate.                                                   | $\mathbb{R}$ | -1                        |
| gamma         | Gradient descent learning rate, not used for conjugate gradient.           | ${[}0, 1{]}$ | 0.00125                   |
| epsilon       | Convergence check, if $\varepsilon$ distance from criterion.               | ${[}0, 1{]}$ | 0.00001                   |
| max\_iter     | Maximum number of iterations if no convergence.                            | $\mathbb{N}$ | \texttt{INT\_MAX}         |
| path          | Path for logging.                                                          | -            | "logs/rosenbrock\_gd.csv" |
