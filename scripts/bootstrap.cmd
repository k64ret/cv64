@rem
@rem Install pip dependencies
@rem
pip install --requirement requirements.txt

@rem
@rem Install Git hooks
@rem
pre-commit install

@rem
@rem Generate tools first
@rem
cmake                  ^
  -G "MinGW Makefiles" ^
  -S ./tools           ^
  -B ./build/tools

@rem
@rem ...then generate main project with appropriate compiler flag
@rem
cmake                                                     ^
  -D CMAKE_C_COMPILER=%cd%/build/tools/ido/windows/7.1/cc ^
  -G "MinGW Makefiles"                                    ^
  -S .                                                    ^
  -B ./build
