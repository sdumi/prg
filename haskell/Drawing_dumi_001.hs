--------------------------------------------------
-- Author:       Dumitru Sipos
-- Date:         20 Aug 2010
-- Name:         Drawing_dumi_001
-- Description:  just some fooling around with gtk and
--                cairo in haskell
--------------------------------------------------
import qualified Graphics.UI.Gtk as G
import qualified Graphics.Rendering.Cairo as C
-- DS: do I need the Matrix here?
import qualified Graphics.Rendering.Cairo.Matrix as M

-- size of main window:
windowWidth, windowHeight :: Int
windowWidth  = 700
windowHeight = 700

-- write image to file
writePng :: IO ()
writePng = 
    C.withImageSurface C.FormatARGB32 width height $ \ result  -> do
      C.renderWith result $ example width height
      C.surfaceWriteToPNG result "Drawing_dumi_001.png"
    where width  = windowWidth
          height = windowHeight

-- Display image in window
main = do
  G.initGUI
  window <- G.windowNew
  canvas <- G.drawingAreaNew
  G.windowSetDefaultSize window windowWidth windowWidth
  -- we can force a mininum size with the following call:
  --G.widgetSetSizeRequest window windowWidth windowHeight
--  G.onKeyPress window $ const (do G.widgetDestroy window; return True)
  G.onDestroy window G.mainQuit
  G.onExpose canvas $ const (updateCanvas canvas)
  G.set window [G.containerChild G.:= canvas]
  G.widgetShowAll window
  G.mainGUI
  writePng

-- the actual drawing is triggered by this method:
--   the method which does the drawing is 'example'
updateCanvas :: G.DrawingArea -> IO Bool
updateCanvas canvas = do
  win <- G.widgetGetDrawWindow canvas
  (width, height) <- G.widgetGetSize canvas
  G.renderWithDrawable win $ 
   example width height
  return True
------------------------------------------------------------------
-- used to draw various figures:
drawCircle x y r = do
  C.arc x y r 0 (2*pi)
  fillStroke

drawRectangle x y w h = do
  C.rectangle x y w h
  fillStroke

fillStroke = do
  C.fillPreserve
  stroke

stroke = do
  keepState $ do
           C.setSourceRGBA 0 0 0 0.7
           C.stroke

keepState render = do
    C.save
    render
    C.restore


foreach :: (Monad m) => [a] -> (a -> m b) -> m [b]
foreach = flip mapM

------------------------------------------------------------------

-- fooling around a little :)
example width height = do
  C.identityMatrix
  C.translate 100 100
  C.scale 5 5
  C.showText "text01"
--  prologue width height
--  drawCircle 0 0 1
--  C.showText "text02"
--  C.save
--  C.translate 4.5 0
--  C.scale 1 1.5
--  drawCircle 0 0 1
--  C.showText "text03"
--  C.restore

-- Set up stuff
prologue wWidth wHeight = do
  let width   = 10
      height  = 10
      xmax    = width / 2
      xmin    = - xmax
      ymax    = height / 2
      ymin    = - ymax
      scaleX  = realToFrac wWidth  / width
      scaleY  = realToFrac wHeight / height

  -- style and color
  C.setLineCap C.LineCapRound
  C.setLineJoin C.LineJoinRound
  C.setLineWidth $ 1 / max scaleX scaleY
  C.setSourceRGBA 0.5 0.7 0.5 0.5

  -- Set up user coordinates
  C.scale scaleX scaleY
  -- center origin
  C.translate (width / 2) (height / 2)
  -- positive y-axis upwards
--  let flipY = M.Matrix 1 0 0 (-1) 0 0
--  C.transform flipY
--  grid xmin xmax ymin ymax


-- Grid and axes
grid xmin xmax ymin ymax =
  keepState $ do
  C.setSourceRGBA 0 0 0 0.7
  -- axes
  C.moveTo 0 ymin; C.lineTo 0 ymax; C.stroke
  C.moveTo xmin 0; C.lineTo xmax 0; C.stroke
  -- grid
  C.setDash [0.01, 0.99] 0
  foreach [xmin .. xmax] $ \ x ->
      do C.moveTo x ymin
         C.lineTo x ymax
         C.stroke

