library(readr)
library(ggplot2)

# Gradient Descent
gd <- read_csv("C:/Marci/Suli/UAB/OPT/Deterministic/Deterministic/logs/rosenbrock_gd.csv", col_names = FALSE)
colnames(gd) <- c("x", "y", "error")

rosenbrock <- function(v) {
  (1 - v[1])^2 + 100 * (v[2] - v[1]*v[1])^2
}

n.grid <- 100
x <- seq(-2, 2, length = n.grid)
y <- seq(-2, 2, length = n.grid)
grid <- expand.grid(x, y)
z <- apply(grid, 1, rosenbrock)##compute the function on the grid
z <- matrix(z, n.grid)

# Contour
contour(x, y, matrix(log10(z), length(x)), xlab="x", ylab="y")
points(gd$x, gd$y, col="red", pch=19)
points(-1.5, -1, col="blue", pch=19)

# Error
ggplot(data = gd) +
  geom_point(aes(y = error, x=c(1:length(error)), col = error, alpha = 0.01))

# Conjugate Gradient
cg <- read_csv("C:/Marci/Suli/UAB/OPT/Deterministic/Deterministic/logs/rosenbrock_cg.csv", col_names = FALSE)
colnames(cg) <- c("x", "y", "error", "norm")

rosenbrock <- function(v) {
  (1 - v[1])^2 + 100 * (v[2] - v[1]*v[1])^2
}

n.grid <- 100
x <- seq(-2, 2, length = n.grid)
y <- seq(-2, 2, length = n.grid)
grid <- expand.grid(x, y)
z <- apply(grid, 1, rosenbrock)##compute the function on the grid
z <- matrix(z, n.grid)

# Contour
contour(x, y, matrix(log10(z), length(x)), xlab="x", ylab="y")
points(cg$x, cg$y, col="red", pch=19)
points(-1.5, -1, col="blue", pch=19)

# Error
ggplot(data = cg) +
  geom_point(aes(y = norm, x=c(1:length(error)), col = error, alpha = 0.01))

