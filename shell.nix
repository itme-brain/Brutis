{ pkgs ? import <nixpkgs> {} }:

# Add more packages to this shell.
# https://search.nixos.org/packages

with pkgs;
mkShell {
  name = "C Dev Env";
  buildInputs = [
    gcc
    glibc
    curl
  ];
  shellHook = ''
  '';
}
