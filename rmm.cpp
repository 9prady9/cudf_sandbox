#include "cuda_runtime_api.h"
#include <iostream>

#include <rmm/device_buffer.hpp>
#include <kvikio/file_handle.hpp>

int main(int argc, char** argv) {

  try {
    RMM_CUDA_TRY(cudaSetDevice(0));
    auto mr = rmm::mr::cuda_memory_resource{};
    rmm::device_buffer buf(10, rmm::cuda_stream_default, &mr);

    std::cout << "Buffer has " << buf.size() << " bytes worth data" << std::endl;

    auto col1_dev_ptr = buf.data();
    size_t size = buf.size();
    off_t file_offset = 0;
    off_t devptr_offset = 0;
    ssize_t bytes_written = 0;

    kvikio::FileHandle file_handle(argv[1], "w", kvikio::FileHandle::m644, false);
    file_handle.write_async((char*)col1_dev_ptr, &size, &file_offset, &devptr_offset, &bytes_written, 0);
    std::cout << "Write requested for " << size << " bytes" << std::endl;
    RMM_CUDA_TRY(cudaStreamSynchronize(0));
    std::cout << "Write Async ended up writing " << bytes_written << " bytes" << std::endl;
    if (bytes_written < 0) {
      throw std::runtime_error(CUFILE_ERRSTR(abs(bytes_written)+CUFILEOP_BASE_ERR));
    }
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    exit(-1);
  }

  return 0;
}
