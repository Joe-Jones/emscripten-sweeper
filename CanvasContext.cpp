#include "CanvasContext.h"

ContextHolder::ContextHolder(val ctx) : m_ctx(ctx) {}

CanvasPathMethods::CanvasPathMethods(val ctx) : ContextHolder(ctx) {}

void CanvasPathMethods::closePath() {
	m_ctx.call<void>("closePath");
}

void CanvasPathMethods::moveTo(double x, double y) {
	m_ctx.call<void>("moveTo", x, y);
}

void CanvasPathMethods::lineTo(double x, double y) {
	m_ctx.call<void>("lineTo", x, y);
}

void CanvasPathMethods::quadraticCurveTo(double cpx, double cpy, double x, double y) {
	m_ctx.call<void>("quadraticCurveTo", cpx, cpy, x, y);
}

void CanvasPathMethods::bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y) {
	m_ctx.call<void>("bezierCurveTo", cp1x, cp1y, cp2x, cp2y, x, y);
}

void CanvasPathMethods::arcTo(double x1, double y1, double x2, double y2, double radius) {
	m_ctx.call<void>("arcTo", x1, y1, x2, y2, radius);
}

void CanvasPathMethods::arcTo(double x1, double y1, double x2, double y2, double radiusX, double radiusY, double rotation) {
	m_ctx.call<void>("arcTo", x1, y1, x2, y2, radiusX, radiusY, rotation);
}

void CanvasPathMethods::rect(double x, double y, double w, double h) {
	m_ctx.call<void>("rect", x, y, w, h);
}

void CanvasPathMethods::arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise) {
	m_ctx.call<void>("arc", x, y, radius, startAngle, endAngle, anticlockwise);
}

CanvasRenderingContext2D::CanvasRenderingContext2D(val context) : CanvasPathMethods(context) {}

void CanvasRenderingContext2D::save() {
	m_ctx.call<void>("save");
}

void CanvasRenderingContext2D::restore() {
	m_ctx.call<void>("restore");
}

void CanvasRenderingContext2D::scale(double x, double y) {
	m_ctx.call<void>("scale", x, y);
}

void CanvasRenderingContext2D::rotate(double angle) {
	m_ctx.call<void>("rotate", angle);
}

void CanvasRenderingContext2D::translate(double x, double y) {
	m_ctx.call<void>("translate", x, y);
}

void CanvasRenderingContext2D::transform(double a, double b, double c, double d, double e, double f) {
	m_ctx.call<void>("transform", a, b, c, d, e, f);
}

void CanvasRenderingContext2D::setTransform(double a, double b, double c, double d, double e, double f) {
	m_ctx.call<void>("setTransform", a, b, c, d, e, f);
}

void CanvasRenderingContext2D::resetTransform() {
	setTransform(1, 0, 0, 1, 0, 0);
}

double CanvasRenderingContext2D::getGlobalAlpha() {
	return m_ctx["globalAlpha"].as<double>();
}

void CanvasRenderingContext2D::setGlobalAlpha(double alpha) {
	m_ctx.set("globalAlpha", val(alpha));
}
  
std::string CanvasRenderingContext2D::getGlobalCompositeOperation() {
	return m_ctx["globalCompositeOperation"].as<std::string>();
}

void CanvasRenderingContext2D::setGlobalCompositeOperation(std::string operation) {
	m_ctx.set("globalCompositeOperation", val(operation));
}

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

void CanvasRenderingContext2D::clearRect(double x, double y, double w, double h) {
	m_ctx.call<void>("clearRect", x, y, w, h);
}

void CanvasRenderingContext2D::fillRect(double x, double y, double w, double h) {
	m_ctx.call<void>("fillRect", x, y, w, h);
}

void CanvasRenderingContext2D::strokeRect(double x, double y, double w, double h) {
	m_ctx.call<void>("strokeRect", x, y, w, h);
}

void CanvasRenderingContext2D::beginPath() {
	m_ctx.call<void>("beginPath");
}

void CanvasRenderingContext2D::fill() {
	m_ctx.call<void>("fill");
}

void CanvasRenderingContext2D::stroke() {
	m_ctx.call<void>("stroke");
}

void CanvasRenderingContext2D::fillText(std::string text, double x, double y) {
	m_ctx.call<void>("fillText", text, x, y);
}

void CanvasRenderingContext2D::fillText(std::string text, double x, double y, double maxWidth) {
	m_ctx.call<void>("fillText", text, x, y, maxWidth);
}
  
