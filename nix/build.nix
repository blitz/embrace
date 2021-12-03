{ stdenv, cmake, nlohmann_json, catch2 }:

stdenv.mkDerivation {
  pname = "embrace";
  version = "0.0.0";

  nativeBuildInputs = [ cmake ];
  buildInputs = [ nlohmann_json ];
  checkInputs = [ catch2 ];

  doCheck = true;
}
