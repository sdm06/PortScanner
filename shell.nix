{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gnumake
    clang-tools # For clangd LSP in Neovim
    valgrind    # To check for memory leaks/race conditions
    netcat
  ];
}
