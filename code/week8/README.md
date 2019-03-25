# Generating numerical results

This tutorial should help you with generating and present numerical results. It contains example code for two helper classes; one for benchmarking, and one for storing numerical results. You can extend and generalize these helper classes for your own experiments.

## Timer class

Using a `timer` object, you can query durations. This should make benchmarking easier:

```cpp
auto dt = timer();
... // compute something
std::cout << "Took: " << dt.get<std::milli>() << " ms\n";
```

## Report class

With a `report` object you can store tabular data. This can then be imported into Python to generate a plot, or converted to a LaTeX table.

```cpp
// make a table with a certain title
auto table = report("<random> benchmarks");
// set the columns of the table
table.columns("engine", "test", "time");
... // generate rows, adding them using table.row(...)

// save as JSON or CSV
table.save_json("data/filename.json");
table.save_csv("data/filename.csv");
```

In the default implementation, only string entries are supported. You can either extend this implementation, or use `std::to_string(x)` on numerical values.

## Plotting using Python

The `scripts` folder contains an example to convert a JSON file saved by the `report` class, to a PNG image. This is done using Python and Matplotlib.

## Using an external library

This code uses an external JSON library. In this Git repository, this is managed through a submodule. Alternatively, you can download a Zip of the library at <https://github.com/nlohmann/json/>, and store it in `ext/json`. This dependency is managed through CMake.
