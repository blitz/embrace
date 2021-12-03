{
  sources ? import ./sources.nix,
  nixpkgs ? sources.nixpkgs,
  pkgs ? import nixpkgs {}
}:

{
  embrace = pkgs.callPackage ./build.nix {};
}
