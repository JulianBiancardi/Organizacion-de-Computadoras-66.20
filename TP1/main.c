#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#include "args_parser.h"
#include "constants.h"
#include "file_writer.h"

int main(int argc, char** argv) {
  char output_file[FILE_NAME_MAX_LEN] = "stdout";
  bool divisor;
  get_arguments(argc, argv, output_file, &divisor);

  file_writer_t file_writer;
  file_writer_init(&file_writer, output_file);

  int result;
  if (divisor == true) {
    result = file_reader_process(&file_reader, decode_and_output, &file_writer);
  } else {
    result = file_reader_process(&file_reader, encode_and_output, &file_writer);
  }

  file_writer_destroy(&file_writer);

  if (result == ERROR) {
    printf(
        "Error procesando el archivo de entrada. Un caracter no pudo ser "
        "decodificado.\n");
    if (output_file != "stdout") {
      remove(output_file);
    }
  }
  return result;
}
