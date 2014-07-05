#include <emscripten/bind.h>
using namespace emscripten;

class ContextHolder {
public:
	ContextHolder(val ctx);
protected:
	val m_ctx;
};

class CanvasPathMethods : public ContextHolder {
public:
  CanvasPathMethods(val ctx);
  // shared path API methods
  void closePath();
  void moveTo(double x, double y);
  void lineTo(double x, double y);
  void quadraticCurveTo(double cpx, double cpy, double x, double y);
  void bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
  void arcTo(double x1, double y1, double x2, double y2, double radius); 
  void arcTo(double x1, double y1, double x2, double y2, double radiusX, double radiusY, double rotation); 
  void rect(double x, double y, double w, double h);
  void arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise = false);
};


class CanvasRenderingContext2D : public CanvasPathMethods {
public:
	CanvasRenderingContext2D(val context);

  // back-reference to the canvas
  //readonly attribute HTMLCanvasElement canvas;

  // state
  void save(); // push state on state stack
  void restore(); // pop state stack and restore state

  // transformations (default transform is the identity matrix)
  //attribute SVGMatrix currentTransform;
  void scale(double x, double y);
  void rotate(double angle);
  void translate(double x, double y);
  void transform(double a, double b, double c, double d, double e, double f);
  void setTransform(double a, double b, double c, double d, double e, double f);
  void resetTransform();

  // compositing
  double getGlobalAlpha(); // (default 1.0)
  void setGlobalAlpha(double alpha);
  std::string getGlobalCompositeOperation(); // (default source-over)
  void setGlobalCompositeOperation(std::string operation);

  // colors and styles (see also the CanvasDrawingStyles interface)
  //         attribute (DOMString or CanvasGradient or CanvasPattern) strokeStyle; // (default black)
  //         attribute (DOMString or CanvasGradient or CanvasPattern) fillStyle; // (default black)
  //CanvasGradient createLinearGradient(double x0, double y0, double x1, double y1);
  //CanvasGradient createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
  //CanvasPattern createPattern(CanvasImageSource image, [TreatNullAs=EmptyString] DOMString repetition);

  // shadows
  //         attribute unrestricted double shadowOffsetX; // (default 0)
   //        attribute unrestricted double shadowOffsetY; // (default 0)
  //         attribute unrestricted double shadowBlur; // (default 0)
  //         attribute DOMString shadowColor; // (default transparent black)

  // rects
  void clearRect(double x, double y, double w, double h);
  void fillRect(double x, double y, double w, double h);
  void strokeRect(double x, double y, double w, double h);

  // path API (see also CanvasPathMethods)
  void beginPath();
  void fill();
  //void fill(optional CanvasFillRule fillRule = "nonzero");
  //void fill(Path path, optional CanvasFillRule fillRule = "nonzero");
  void stroke();
  //void stroke(Path path);
  //void drawSystemFocusRing(Element element);
  //void drawSystemFocusRing(Path path, Element element);
  //boolean drawCustomFocusRing(Element element);
  //boolean drawCustomFocusRing(Path path, Element element);
  //void scrollPathIntoView();
  //void scrollPathIntoView(Path path);
  //void clip(optional CanvasFillRule fillRule = "nonzero");
  //void clip(Path path, optional CanvasFillRule fillRule = "nonzero");
  //void resetClip();
  //boolean isPointInPath(unrestricted double x, unrestricted double y, optional CanvasFillRule fillRule = "nonzero");
  //boolean isPointInPath(Path path, unrestricted double x, unrestricted double y, optional CanvasFillRule fillRule = "nonzero");
  //boolean isPointInStroke(unrestricted double x, unrestricted double y);
  //boolean isPointInStroke(Path path, unrestricted double x, unrestricted double y);

  // text (see also the CanvasDrawingStyles interface)
  void fillText(std::string text, double x, double y);
  void fillText(std::string text, double x, double y, double maxWidth);
  //void strokeText(DOMString text, unrestricted double x, unrestricted double y, optional unrestricted double maxWidth);
  //TextMetrics measureText(DOMString text);

  // drawing images
  //void drawImage(CanvasImageSource image, unrestricted double dx, unrestricted double dy);
  //void drawImage(CanvasImageSource image, unrestricted double dx, unrestricted double dy, unrestricted double dw, unrestricted double dh);
  //void drawImage(CanvasImageSource image, unrestricted double sx, unrestricted double sy, unrestricted double sw, unrestricted double sh, unrestricted double dx, unrestricted double dy, unrestricted double dw, unrestricted double dh);

  // hit regions
  //void addHitRegion(optional HitRegionOptions options);
  //void removeHitRegion(DOMString id);

  // pixel manipulation
  //ImageData createImageData(double sw, double sh);
  //ImageData createImageData(ImageData imagedata);
  //ImageData createImageDataHD(double sw, double sh);
  //ImageData getImageData(double sx, double sy, double sw, double sh);
  //ImageData getImageDataHD(double sx, double sy, double sw, double sh);
  //void putImageData(ImageData imagedata, double dx, double dy);
  //void putImageData(ImageData imagedata, double dx, double dy, double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight);
  //void putImageDataHD(ImageData imagedata, double dx, double dy);
  //void putImageDataHD(ImageData imagedata, double dx, double dy, double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight);
};
