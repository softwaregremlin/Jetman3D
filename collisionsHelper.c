// Helper function
unsigned int Between(float value, float min, float max) {
	return value >= min && value <= max;
}

// Helper function
unsigned int InRectangle(float x, float y, float left, float top, float width, float height) {
	return Between(x, left, left + width) &&
		Between(y, top - height, top);
}

// Helper function
unsigned int RectanglesCollide(float left1, float top1, float width1, float height1,
	float left2, float top2, float width2, float height2) {
	return (InRectangle(left1, top1, left2, top2, width2, height2) ||
		InRectangle(left1 + width1, top1, left2, top2, width2, height2) ||
		InRectangle(left1, top1 - height1, left2, top2, width2, height2) ||
		InRectangle(left1 + width1, top1 - height1, left2, top2, width2, height2))
		||
		(InRectangle(left2, top2, left1, top1, width1, height1) ||
			InRectangle(left2 + width2, top2, left1, top1, width1, height1) ||
			InRectangle(left2, top2 - height2, left1, top1, width1, height1) ||
			InRectangle(left2 + width2, top2 - height2, left1, top1, width1, height1));
}