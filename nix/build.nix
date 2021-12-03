{ stdenv, cmake, json_c, pkg-config }:

stdenv.mkDerivation {
  pname = "embrace";
  version = "0.0.0";

  nativeBuildInputs = [ cmake pkg-config ];
  buildInputs = [ json_c ];

}
