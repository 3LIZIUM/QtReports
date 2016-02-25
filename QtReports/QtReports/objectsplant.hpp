#pragma once
#ifndef OBJECTSPLANT_HPP
#define OBJECTSPLANT_HPP
#include <QMap>
#include <QString>
#include "tags/object.hpp"

namespace qtreports {
	namespace detail {

		/* Фабрика объектов, возвращает объект и карту его параметров. */
		class ObjectsPlant {

		public:
			ObjectsPlant();

			Object *				getObject( const QString & name ) const;
			QMap<QString, QString>	getParamTypeMap( const QString & name ) const;

		};

	}
}

#endif // OBJECTSPLANT_HPP
