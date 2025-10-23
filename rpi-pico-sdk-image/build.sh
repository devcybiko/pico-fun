#!/bin/bash
set -e

DOCKER="docker"
# DOCKER="podman"

### If you're getting Error statfs no such file or directory init the machine as follows:
### With the "-v" option pointing to the volume you're having trouble mounting
# podman machine init podman-machine-default -v /Volumes/GregsGit
# podman machine start

# these are more dangerous that I thought
# yes | podman container prune
# yes | podman image prune

$DOCKER build -t rpi-pico-sdk-image .
$DOCKER run -p 8443:8443 --name RPi-Pico-SDK rpi-pico-sdk-image
$DOCKER commit RPi-Pico-SDK rpi-pico-sdk-container
