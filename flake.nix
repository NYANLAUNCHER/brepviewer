{
  description = "An incomplete BREP (Boundary REPresentation) viewer written in CPP using OpenGL.";

  inputs.nixpkgs.url = "nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
    ##########################################
    pname = "brepviewer";
    version = "0.1.0";
    nativeBuildInputs = with pkgs; [ # build-time dependencies
        pkg-config autoconf automake gcc
    ];
    buildInputs = with pkgs; [ # runtime dependencies
      libGL
      libGLU
      glew
      glfw
      glm
      assimp
    ];
    ##########################################
  in {
    defaultPackage.${system} = pkgs.stdenv.mkDerivation {
      inherit pname version buildInputs nativeBuildInputs;
      src = ./.;
      buildPhase = ''
        make
      '';
      installPhase = ''
        make install
      '';
    };
    devShells.${system}.default = pkgs.mkShell {
      inherit buildInputs;
      nativeBuildInputs = with pkgs; [
        #glxinfo
        lldb
        gdb
        renderdoc
        unixtools.xxd
      ] ++ nativeBuildInputs;
      shellHook = ''
        export pname=${pname}
        export out=""
      '';
    };
  };
}
