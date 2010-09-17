{- LSystems.hs
 -
 - Matthew Blissett
 - November 2006
 -
 - Based first year coursework from http://www.doc.ic.ac.uk/...
 -
 - Displays an L-System described by set of rules given.
 -
 - Start hugs with the -h50M option, i.e.
 -     hugs -h50M LSystems.hs
 - and type
 -     main n
 - where 'n' is the L-System to show. Use '+' and '-' to increase the
 - number of iterations of the system to show. Press 'q' to quit.
 -}

import Graphics.UI.GLUT
import Graphics.Rendering.OpenGL
import Data.IORef
import System.Exit (exitWith, ExitCode(ExitSuccess))

type Rule = (Char, String)

type MyVertex = (Float, Float)
type MyColor = (Float, Float, Float)
type MyPoint = (MyVertex, MyColor)
type MyPolyline = [MyPoint]

-- Draws an L-System
-- Int: L-System to draw (i.e. rules to use)
--main :: Int -> IO ()
--main n = do
main = do
        getArgsAndInitialize      
        points <- newIORef []
	iterations <- newIORef 2

	lsystems <- newIORef []
	lsystems $= lSystemList n

	initialDisplayMode $= [ DoubleBuffered, RGBMode ]
	initialWindowSize $= Size 250 250
	createWindow ("L Systems - System " ++ (show n))

	calculateSystem lsystems iterations points
	keyboardMouseCallback $= Just (keyboard lsystems iterations points)
	displayCallback $= display points
	mainLoop
    where n = 1

calculateSystem :: IORef [[MyPolyline]] -> IORef Int -> IORef [MyPolyline] -> IO ()
calculateSystem lsystems' iterations' points' = do
	iterations <- get iterations'
	lsystems <- get lsystems'
	print ("Showing " ++ (show iterations) ++ " iterations")
	print "Finding limits..."
	let lsystem = lsystems !! iterations
	let limits = findLimits (concat lsystem)
	points' $= map (map (scalePoints limits)) lsystem

	clearColor $= Color4 0 0 0 0
	matrixMode $= Projection
	loadIdentity
	let b = 0.01
	ortho (0-b) (1+b) (0-b) (1+b) 0 10

	where
		-- Finds outermost points in L-System
		findLimits :: MyPolyline -> (Float, Float, Float, Float)
		findLimits (((x, y), _):ps) = findLimits' (x, x, y, y) ps
		findLimits' (xL, xH, yL, yH) [] = (xL, xH, yL, yH)
		findLimits' (xL, xH, yL, yH) (((x, y), _):ps) = findLimits' (min x xL, max x xH, min y yL, max y yH) ps
		-- Would be better implemented with a fold (although this is probably quicker)

-- Converts all points to be in the range (0,1) for x and y.
scalePoints :: (Float, Float, Float, Float) -> MyPoint -> MyPoint
scalePoints (xL, xH, yL, yH) ((x, y), c) = (((x - xL) / (xH - xL) * 1, (y - yL) / (yH - yL) * 1), c)

-- Handles keyboard events
keyboard :: IORef [[MyPolyline]] -> IORef Int -> IORef [MyPolyline] -> Key -> KeyState -> a -> b -> IO ()
keyboard lsystems' iterations' points' (Char a) Down _ _ = case a of
	'+' -> do
		i <- get iterations'
		iterations' $= i + 1
		calculateSystem lsystems' iterations' points'
		postRedisplay Nothing
	'-' -> do
		i <- get iterations'
		iterations' $= max (i - 1) 0
		calculateSystem lsystems' iterations' points'
		postRedisplay Nothing
	'q' -> exitWith ExitSuccess
	'\27' -> exitWith ExitSuccess
	other -> return ()
keyboard _ _ _ _ _ _ _ = return ()

-- Handles redisplaying
display :: IORef [MyPolyline] -> DisplayCallback
display points = do
	points <- get points
	clear [ColorBuffer]
	print "Rendering lines..."
	renderPolylines points
	print "Done"
	swapBuffers

-- Turns goblins into polylines.
renderPolylines :: [MyPolyline] -> IO ()
renderPolylines points = mapM_ (\a -> renderPolyline (mapM_ lineSegmentToPoint a)) points

renderPolyline :: IO () -> IO ()
renderPolyline a = renderPrimitive LineStrip $ a

lineSegmentToPoint :: MyPoint -> IO ()
lineSegmentToPoint ((x,y), (r,g,b)) = (color $ Color3 r g b) >> (vertex $ Vertex3 x y 0.0)

-- Example L-Systems
-- Int: system to select
system :: Int -> (Float, String, [Rule], MyColor -> MyColor)

-- Cross
system 1 = (pi/2, "M-M-M-M", [('M', "M-M+M+MM-M-M+M"),
                              ('+', "+"),
                              ('-', "-")], \(r, g, _) -> let r' = if (r + 0.01 > 1) then 0 else (r + 0.01) in let g' = if (g - 0.02 < 0) then 1 else (g - 0.02) in (r', g', 0))

-- Triangle
system 2 = (pi/2, "-M", [('M', "M+M-M-M+M"),
                         ('+', "+"),
                         ('-', "-")], id)

-- Arrowhead
system 3 = (pi/3, "N", [('M', "N+M+N"),
                        ('N', "M-N-M"),
                        ('+', "+"),
                        ('-', "-")], id)

-- Peano-Gosper
system 4 = (pi/3, "M", [('M', "M+N++N-M--MM-N+"),
                        ('N', "-M+NN++N+M--M-N"),
                        ('+', "+"),
                        ('-', "-")], (\(r, _, b) -> let r' = if (r < 0.3) then 0.0 else (1 - r + 0.3) in (b, 0, r')))

-- Dragon
system 5 = (pi/4, "MX", [('M', "A"),
                         ('X', "+MX--MY+"),
                         ('Y', "-MX++MY-"),
                         ('A', "A"),
                         ('+', "+"),
                         ('-', "-")], id)

-- Snowflake
system 6 = (pi/3, "M--M--M", [('M', "M+M--M+M"),
                              ('+', "+"),
                              ('-', "-")], (\(_, _, b) -> let x = if (b + 0.05 > 1) then 0.5 else (b + 0.05) in (x - 0.1, x - 0.1, x)))

-- Tree
system 7 = (pi/4, "M", [('M', "N[-M][+M][NM]"),
                        ('N', "NN"),
                        ('[', "["),
                        (']', "]"),
                        ('+', "+"),
                        ('-', "-")], nextColor)

-- Bush
system 8 = (pi/8, "X", [('X', "M-[[X]+X]+M[+MX]-X"),
                        ('M', "MM"),
                        ('[', "["),
                        (']', "]"),
                        ('+', "+"),
                        ('-', "-")], nextColor)

-- http://shakti.trincoll.edu/~cschneid/lsystems.html
system 9 = (pi/6, "M", [('M', "N[-M][+M]NM"),
                        ('N', "NN"),
                        ('[', "["),
                        (']', "]"),
                        ('+', "+"),
                        ('-', "-")], nextColor)

-- Makes interesting patterns with colours
-- MyColor: colour to convert from
nextColor :: MyColor -> MyColor
nextColor (r, g, b) = (f (r + 0.03), f (g + 0.05), f (b - 0.07))
	where
		f n | n > 1.0 = 0.0
			| n < 0.0 = 1.0
			| True	  = n

-- Rules for converting L-System structures into movement commands
mapper :: [Rule]
mapper = [('M', "F"),
          ('N', "F"),
          ('X', ""),
          ('Y', ""),
          ('A', ""),
          ('[', "["),
          (']', "]"),
          ('+', "L"),
          ('-', "R")]

-- Successive iterations of an L-System expressed as a list of polylines.
-- Int: L-System rules to use
lSystemList :: Int -> [[MyPolyline]]
lSystemList n = map traceSystem iterations
	where
		(angle, base, rules, colorCycle) = system n
		iterations = iterate (expand rules) base
		traceSystem l = trace (expand mapper l) angle colorCycle

-- Produces a single L-System of required iteration
-- Int: L-System rules to use
-- Int: Iteration number
lSystem :: Int -> Int -> [MyPolyline]
lSystem n i = lSystemList n !! i

-- Expands command string once using rules
-- [Rule]: rules for expansion
-- String: command string
expand :: [Rule] -> String -> String
expand rules string = concat $ map expand' string
	where
		expand' :: Char -> String
		expand' c = head([y | (x,y) <- rules, x == c])

-- Converts list of movement commands into list of lines defined by vertices
-- String: list of movement commands "FFRBFF" etc
-- Float: angle to use for rotations
-- (MyColor -> MyColor): function to change colour of points in some way
trace :: String -> Float -> (MyColor -> MyColor) -> [MyPolyline]
trace [] _ _ = []
trace commands angle cc = trace' [startPoint] (pi/2) commands
	where
		startPoint :: MyPoint
		startPoint = ((0.0, 0.0), (0.5, 0.5, 0.5))
		-- MyPolyline: line currently being described
		-- Float: current angle
		-- String: remaining movement commands
		trace' :: MyPolyline -> Float -> String -> [MyPolyline]
		trace' line _ [] = [line]
		trace' line _ (']':ls) = [line]
		trace' line angle ('[':ss) = branchSegment ++ remainingSegment
			where
				branchSegment :: [MyPolyline]
				branchSegment = trace' line angle ss
				remainingSegment :: [MyPolyline]
				remainingSegment = trace' [head line] angle (afterClose 0 ss)
				-- Drops characters from a string until the matching ']' is found
				afterClose :: Int -> String -> String
				afterClose 0 (']':ss) = ss
				afterClose n (']':ss) = afterClose (n-1) ss
				afterClose n ('[':ss) = afterClose (n+1) ss
				afterClose n (s:ss) = afterClose n ss
		trace' line oldAngle (s:ss) = trace' (newPoint : line) newAngle ss
			where
				(newPoint, newAngle) = move s (head line, oldAngle) angle cc

-- Moves turtle: 'F' moves distance 1, 'L' and 'R' rotate left and right
-- by given angle, cycle colour of point at each 'F'
-- Char: Command character
-- (MyPoint, Float): Current point and angle
-- (MyColor -> MyColor): Colour changing function
move :: Char -> (MyPoint, Float) -> Float -> (MyColor -> MyColor) -> (MyPoint, Float)
move 'F' (((x, y), c), r) _ cc = (((x + cos r, y + sin r), cc c), r)
move 'L' (p, r) a cc = (p, r + a)
move 'R' (p, r) a cc = (p, r - a)
