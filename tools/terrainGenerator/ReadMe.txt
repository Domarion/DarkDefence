Options: 
path to config file
path to output file

Atlas or image path declared in config file.

Empty actual config placed in conf directory.

Conf file also contain information for path generation.

FilledCell = -2;
EmptyCell = -1;

-- Tile width and tile height--
-- Atlas path. !none! is received for separate image loading. --
-- In case of separate loading grass means part of image name --
-- Images search path in <current bin path>/tiles/ --
-- Count of unique tiles --
-- Tile definition in format: --
-- Mandatory fields:
--      Letter used in tilematrix, --
--      Path -1 can path, -2 no path --
--      Tilename sufficient only in separate loading case --
-- Atlas fields (present only if atlas not equas !none!): --
-- Position x y (from top left corner) --
-- Tile matrix used for resulting image and pathmap generation --
-- First is row in matrix, second is column --
-- Tile matrix --
