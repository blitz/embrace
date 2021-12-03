{ stdenv, cmake, nlohmann_json, catch2, nix-gitignore }:

stdenv.mkDerivation {
  pname = "embrace";
  version = "0.0.0";

  src = nix-gitignore.gitignoreSource [] ../src;

  nativeBuildInputs = [ cmake ];
  buildInputs = [ nlohmann_json ];
  checkInputs = [ catch2 ];

  doCheck = true;
}
