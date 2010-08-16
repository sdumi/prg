module Paths_rwh (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName
  ) where

import Data.Version (Version(..))
import System.Environment (getEnv)

version :: Version
version = Version {versionBranch = [0,1], versionTags = []}

bindir, libdir, datadir, libexecdir :: FilePath

bindir     = "/home/dsipos/.cabal/bin"
libdir     = "/home/dsipos/.cabal/lib/rwh-0.1/ghc-6.12.1"
datadir    = "/home/dsipos/.cabal/share/rwh-0.1"
libexecdir = "/home/dsipos/.cabal/libexec"

getBinDir, getLibDir, getDataDir, getLibexecDir :: IO FilePath
getBinDir = catch (getEnv "rwh_bindir") (\_ -> return bindir)
getLibDir = catch (getEnv "rwh_libdir") (\_ -> return libdir)
getDataDir = catch (getEnv "rwh_datadir") (\_ -> return datadir)
getLibexecDir = catch (getEnv "rwh_libexecdir") (\_ -> return libexecdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
