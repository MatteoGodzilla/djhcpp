{
    description = "djhcpp";
    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    };
    outputs = {self, nixpkgs}:
    let 
        system = "x86_64-linux";
        pkgs = import nixpkgs { inherit system; };
    in
    {
        packages.${system}.default = pkgs.stdenv.mkDerivation {
            name = "djhcpp";
            src = pkgs.fetchgit {
                url="https://github.com/MatteoGodzilla/djhcpp.git";
                rev="v0.2.9";
                fetchSubmodules = true;
                deepClone = true;
                hash="sha256-t8aQo64K4eK0TEjRjgdk/iwYueflHrTRmrHC/Q9Ff84=";
            };
            buildInputs = [ 
                pkgs.cmake
                pkgs.wxwidgets_3_3
                pkgs.curlFull
                pkgs.cpm-cmake
            ];
            buildPhase = ''
                runHook preBuild
                ./build-release.sh
                runHook postBuild
            '';
            installPhase = ''
                runHook preInstall
                mkdir -p $out/bin
                cp ./build/djhcpp $out/bin
                runHook postInstall
            '';
        };
    };
}
