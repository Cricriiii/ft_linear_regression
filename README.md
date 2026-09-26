*This project has been created as part of the 42 curriculum by cgajean.*

# ft_linear_regression

## Description

`ft_linear_regression` is an introduction to machine learning: implementing, without any ML library, a linear regression algorithm trained by gradient descent, in order to predict a car's price from its mileage.

The project is written in **C++23** (rather than Python, unlike most implementations of this 42 subject) and relies on two C++ libraries to stay out of "reinventing NumPy/matplotlib from scratch" territory while keeping the actual regression logic hand-written:

- **[NumCpp](https://github.com/dpilger26/NumCpp)** provides the `NdArray` container and vectorized array operations (element-wise arithmetic, reductions, linear algebra) — the C++ equivalent of NumPy. It's used to hold the dataset and run the gradient descent update step without hand-rolled loops over raw arrays.
- **[matplotlib-cpp](https://github.com/lava/matplotlib-cpp)** is a thin C++ wrapper that embeds a CPython interpreter to drive `matplotlib` directly from C++ code. It's what lets `train` plot the regression line and the cost function's evolution without a separate Python script — at the cost of linking against `libpython` and `numpy`'s C headers at build time (see Requirements below).

The project is split into three independent programs:

- **`train`** — reads a `(mileage, price)` dataset, trains the model via gradient descent (with data normalization) and saves the learned parameters `theta0`/`theta1`. Also plots the regression line and the cost function's evolution using matplotlib-cpp.
- **`predict`** — loads the trained parameters and estimates a price for a given mileage (`price = theta0 + theta1 * mileage`). Before any training, `theta0` and `theta1` are 0, so the program still runs and simply returns a null estimate.
- **`precision`** — computes the model's precision (42 subject bonus) by comparing predictions against the dataset's actual values.

An additional utility (`make regression`) generates a synthetic `(x, y)` dataset via `scikit-learn`, to test the model's generalization beyond the single mileage/price dataset provided.

## Project structure

```
ft_linear_regression/
├── data/
│   └── data.csv                 # (mileage, price) dataset provided by the subject
├── linear_regression/
│   ├── include/                 # headers shared by the 3 binaries
│   ├── source/                  # shared implementation (regression, NumCpp helpers)
│   ├── train.cpp
│   ├── predict.cpp
│   ├── precision.cpp
│   └── Makefile                 # actual build of the 3 binaries
├── Makefile                     # entry point: orchestrates linear_regression/'s Makefile
├── Dockerfile
└── README.md
```

> The exact contents of `include/` and `source/` may have evolved slightly since this README was written — refer to the code for the precise file list.

## Instructions

### Requirements

- `g++` with C++23 support
- `make`
- `git`
- `python3` with development headers (`python3-dev`), `python3-numpy`, `python3-matplotlib` and `python3-sklearn`
- `docker` as an alternative to local build

### Build

From the repository root:

```sh
make
```

This clones [NumCpp](https://github.com/dpilger26/NumCpp) and [matplotlib-cpp](https://github.com/lava/matplotlib-cpp) automatically if needed, then builds the three binaries in parallel (`-j`) inside `linear_regression/`.

Other useful targets:

| Target | Effect |
|---|---|
| `make re` | `fclean` then `all` |
| `make rere` | `reset` then `all` (starts from scratch, including cloned dependencies) |
| `make clean` | removes object files |
| `make fclean` | `clean` + removes the executables |
| `make reset` | `fclean` + removes `NumCpp`/`matplotlib-cpp` |
| `make regression` | generates a synthetic `(x, y)` dataset into `data/generated.csv` |
| `make format` | formats the code with `clang-format` |
| `make help` | lists available targets |

### Run

```sh
./linear_regression/train      # trains the model on data/data.csv
./linear_regression/predict    # prompts for a mileage and prints the estimated price
./linear_regression/precision  # prints the trained model's precision
```

### Docker

A `Dockerfile` and matching Makefile targets are provided to build and run the project in an isolated Fedora environment, without installing any dependency on the host:

```sh
make docker       # builds the "linear:1.0" image (runs fclean first)
make docker_run    # runs the image interactively
```

## Resources

**Linear regression and gradient descent**
- [Wikipedia — Linear regression](https://en.wikipedia.org/wiki/Linear_regression)
- [Machine Learnia](https://www.youtube.com/@MachineLearnia)

**C++ tooling**
- [NumCpp documentation](https://dpilger26.github.io/NumCpp/doxygen/html/index.html)
- [matplotlib-cpp (repository README)](https://github.com/lava/matplotlib-cpp)
- [GNU Make Manual](https://www.gnu.org/software/make/manual/make.html) — particularly the sections on recursive make and the jobserver (`-j`), used for this project's build system

**AI usage**

Claude (Anthropic) was used to help design and debug the build system (Makefile architecture) and to draft this README. The linear regression implementation and the NumCpp/matplotlib-cpp integration are original work.