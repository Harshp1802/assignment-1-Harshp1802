all: build

build: binaries
  @echo "Building"
  gcc shell.c -o shell

binaries:
  @echo "Building ls..."
  gcc ls.c -o ls

clean:
  @echo "Cleaning"
  rm ls
  rm shell
