./compile.sh
compile_return=$?
if [ $compile_return -eq 0 ]; then
  ./a.out
  program_return=$?
  if [ $program_return -eq 1 ]; then
    echo "Program finished with error."
    exit 1
  fi
  if [ $program_return -eq 0 ]; then
    echo "Program finished without error."
    exit 0
  fi
fi
if [ $compile_return -eq 1 ]; then
  echo "Compile phase finished with error, can't run program."
  exit 1
fi
