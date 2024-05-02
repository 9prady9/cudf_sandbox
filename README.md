# Requirements

- cuda toolkit (required for calling stream sync)
- cudf
- kvikio

# How to create conda environment

## CUDF 24.04
```bash
mamba create -n cudf_sandbox_24_04 -c rapidsai -c conda-forge -c nvidia python=3.10 libcudf=24.04.* libcufile=1.8.* cuda-cudart-dev=12.3.* cmake=3.29.* cuda-nvcc=12.3.*
```

## CUDF 24.02
```bash
mamba create -n cudf_sandbox_24_02 -c rapidsai -c conda-forge -c nvidia python=3.10 libcudf=24.02.* libcufile=1.8.* cuda-cudart-dev=12.3.* cmake=3.29.* cuda-nvcc=12.3.*
```

# How to build the program

1. `mkdir build && cd build`
2. `cmake ..`
3. `make`

# How to run the program

From the project root run the following command.

```bash
./build/cudf_gds_check.run <full-path-gds-capable-file>
```

The path is mandatory, the program will not work otherwise.

Post run, you should be able to find the `cufile.log` file in the project root which should have any errors encountered
by this program while trying to write a column of 10 bytes to disk. Upon successful write, you should be able to find a
file of size 10 bytes with the name you provided as the argument at the provided location.
