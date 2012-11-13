#!/bin/bash
external/closure-library/closure/bin/build/closurebuilder.py \
  --root=external/closure-library/ \
  --root=src/ui/ \
  --namespace="playtolearn.QuestCanvas" \
  --output_mode=script \
  --compiler_jar=external/closure-compiler/compiler.jar \
  --compiler_flags="--debug" \
  --compiler_flags="--warning_level=VERBOSE" \
  --compiler_flags="--compilation_level=ADVANCED_OPTIMIZATIONS" \
> build/ui/playtolearn.js