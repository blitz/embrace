let
  sources = import ./nix/sources.nix;
  nixpkgs = sources.nixpkgs;
  pkgs = import nixpkgs {};

  local = import ./nix/release.nix { inherit sources nixpkgs pkgs; };
in

pkgs.mkShell {
  inputsFrom = [
    local.embrace
  ];

  nativeBuildInputs = with pkgs; [
    # Development Convenience
    ninja
    cmakeCurses
    gdb

    # Dependency Management
    niv

    # Formatting
    clang-tools                 # clang-format
    nixfmt
  ];
}
