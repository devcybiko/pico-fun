_projects="${1:-./projects}"
projects=`realpath $_projects`
echo "Using projects directory: $projects"
# podman machine stop ### you may need to restart the podman machine
# podman machine start ### if you get permissions errors on ./projects
podman run -it -p 8443:8443 -v "$projects:/home/projects" rpi-pico-sdk-container  /usr/local/bin/login.sh
