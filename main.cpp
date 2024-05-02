#include "cuda_runtime_api.h"
#include <iostream>

#include <cudf/table/table.hpp>
#include <cudf_test/column_wrapper.hpp>
#include <kvikio/file_handle.hpp>

int main(int argc, char** argv) {
  cudf::test::fixed_width_column_wrapper<int8_t> As{{65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
  cudf::test::fixed_width_column_wrapper<int32_t> Seq{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

  auto col1 = As.release();
  auto col2 = Seq.release();

  std::vector<std::unique_ptr<cudf::column>> cols;
  cols.emplace_back(std::move(col1));
  cols.emplace_back(std::move(col2));
  auto table = std::make_unique<cudf::table>(std::move(cols));

  auto table_view = table->select({0, 1});

  try {
    auto col_view = table_view.column(0);
    std::size_t size = col_view.size() * sizeof(int8_t);
    std::cout << "Column " << 0 << " has " << col_view.size() << " bytes worth data" << std::endl;

    auto col1_dev_ptr = col_view.data<int8_t>();
    off_t file_offset = 0;
    off_t devptr_offset = 0;
    ssize_t bytes_written = 0;

    kvikio::FileHandle file_handle(argv[1], "w", kvikio::FileHandle::m644, false);
    file_handle.write_async((char*)col1_dev_ptr, &size, &file_offset, &devptr_offset, &bytes_written, 0);
    std::cout << "Write requested for " << size << " bytes" << std::endl;
    CUDF_CUDA_TRY(cudaStreamSynchronize(0));
    std::cout << "Write Async ended up writing " << bytes_written << " bytes" << std::endl;
    if (bytes_written < 0) {
      throw std::runtime_error(CUFILE_ERRSTR(bytes_written));
    }
  } catch (kvikio::CUfileException &e) {
    std::cout << "Error: " << e.what() << std::endl;
    exit(-1);
  }

  return 0;
}
