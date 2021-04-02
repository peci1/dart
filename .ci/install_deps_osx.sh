#!/usr/bin/env bash
set -e

brew update > /dev/null
brew bundle || brew bundle

# Use pip for the default Python3 version
py_version=$(python3 -c "import sys; print('{}.{}'.format(sys.version_info[0], sys.version_info[1]))")
py_version_major=$(echo $py_version | cut -d. -f1)
pip$py_version_major install -U numpy pytest
