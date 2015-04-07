/*******************************
Copyright (C) 2013-2015 gregoire ANGERAND

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************/

#ifndef N_SCRIPT_DYNAMIC_PRIMITIVE_H
#define N_SCRIPT_DYNAMIC_PRIMITIVE_H

#include "PrimitieType.h"
#include "Primitive.h"
#include <n/defines.h>
#ifndef N_NO_SCRIPT

namespace n {
namespace script {

class DynamicPrimitive
{

	public:
		DynamicPrimitive();
		DynamicPrimitive(const DynamicPrimitive &t);
		DynamicPrimitive(PrimitiveType t, Primitive value = Primitive());

		DynamicPrimitive &operator=(const DynamicPrimitive &t);

		bool operator==(const DynamicPrimitive &o) const;
		bool operator!=(const DynamicPrimitive &o) const;

		Primitive toType(PrimitiveType t) const;

		PrimitiveType &type() {
			return *reinterpret_cast<PrimitiveType *>((void *)raw);
		}

		Primitive &data() {
			void *t = raw + 1;
			return *reinterpret_cast<Primitive *>(t);
		}

		const PrimitiveType &type() const {
			return *reinterpret_cast<PrimitiveType *>((void *)raw);
		}

		const Primitive &data() const {
			const void *t = raw + 1;
			return *reinterpret_cast<const Primitive *>(t);
		}

	private:
		uint16 raw[3];

		bool equals(const Primitive &o) const;
};

}
}

#endif


#endif // N_SCRIPT_DYNAMIC_PRIMITIVE_H
