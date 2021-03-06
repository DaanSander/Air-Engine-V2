#include "Matrix4f.h"

namespace engine {
	namespace math {

		Matrix4f::Matrix4f(fl32 diagonal) {
			for (int i = 0; i < 16; i++) {
				mElements[i] = 0.0f;
			}

			mElements[0 + 0 * 4] = diagonal;
			mElements[1 + 1 * 4] = diagonal;
			mElements[2 + 2 * 4] = diagonal;
			mElements[3 + 3 * 4] = diagonal;
		}

		Matrix4f Matrix4f::identity() {
			return Matrix4f(1.0f);
		}

		Matrix4f Matrix4f::multiply(const Matrix4f& other) const {
			Matrix4f out;
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					fl32 o = 0;
					for (int c = 0; c < 4; c++) {
						o += this->mElements[c + y * 4] * other.mElements[x + c * 4];
					}
					out.mElements[x + y * 4] = o;
				}
			}
			return out;
		}

		Matrix4f Matrix4f::rotation(const Vector3f& axis, fl32 angle) {
			Matrix4f out(1.0f);

			fl32 s = (fl32)sin(degToRad(angle));
			fl32 c = (fl32)cos(degToRad(angle));
			fl32 omc = 1 - c;

			fl32 x = axis.x;
			fl32 y = axis.y;
			fl32 z = axis.z;

			out.mElements[0 + 0 * 4] = c + x * omc;
			out.mElements[1 + 0 * 4] = y * x * omc - z * s;
			out.mElements[2 + 0 * 4] = x * z * omc - y * s;

			out.mElements[0 + 1 * 4] = y * x * omc + z * s;
			out.mElements[1 + 1 * 4] = c + y * omc;
			out.mElements[2 + 1 * 4] = y * z * omc + x * s;

			out.mElements[0 + 2 * 4] = z * x * omc + y * s;
			out.mElements[1 + 2 * 4] = z * y * omc - x * s;
			out.mElements[2 + 2 * 4] = c + z * omc;

			return out;
		}

		Matrix4f Matrix4f::perspective(fl32 ar, fl32 fov, fl32 near, fl32 far) {
			Matrix4f out;
			//tanh or tan
			fl32 tanHalf = (fl32)tan(degToRad(fov) / 2.0f);

			out.mElements[0 + 0 * 4] = 1.0f / (ar * tanHalf);
			out.mElements[1 + 1 * 4] = 1.0f / tanHalf;

			out.mElements[2 + 2 * 4] = -((far + near) / (far - near));
			out.mElements[2 + 3 * 4] = -((2.0f * far * near) / (far - near));

			out.mElements[3 + 2 * 4] = -1.0f;

			return out;
		}

		Matrix4f Matrix4f::orthographic(fl32 near, fl32 far, fl32 top, fl32 bottom, fl32 left, fl32 right) {
			Matrix4f out(1.0f);

			out.mElements[0 + 0 * 4] = 2.0f / (right - left);
			out.mElements[3 + 0 * 4] = -((right + left) / (right - left));

			out.mElements[1 + 1 * 4] = 2.0f / (top - bottom);
			out.mElements[3 + 1 * 4] = -((top + bottom) / (top - bottom));

			out.mElements[2 + 2 * 4] = -2.0f / (far - near);
			out.mElements[3 + 2 * 4] = -((far + near) / (far - near));

			out.mElements[3 + 3 * 4] = 1.0f;

			return out;
		}


		Matrix4f Matrix4f::translation(const Vector3f& position) {
			Matrix4f out(1.0f);

			out.mElements[0 + 3 * 4] = position.x;
			out.mElements[1 + 3 * 4] = position.y;
			out.mElements[2 + 3 * 4] = position.z;

			return out;
		}

		Matrix4f Matrix4f::scale(const Vector3f& scale) {
			Matrix4f out(1.0f);

			out.mElements[0 + 0 * 4] = scale.x;
			out.mElements[1 + 1 * 4] = scale.y;
			out.mElements[2 + 2 * 4] = scale.z;

			return out;
		}

		Matrix4f Matrix4f::transformation(const Matrix4f& translation, const Matrix4f& rotation, const Matrix4f& scale) {
			return (scale * rotation) * translation;
		}

		Matrix4f operator*(const Matrix4f& a, const Matrix4f& b) {
			return a.multiply(b);
		}
} }