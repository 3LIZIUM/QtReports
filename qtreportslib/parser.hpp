#pragma once
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <functional>
#include <QString>
#include <QXmlStreamReader>
#include <QMap>
#include <QTextStream>
#include "tags/report.hpp"
#include "tags/style.hpp"
#include "tags/field.hpp"
#include "tags/detail.hpp"
#include "tags/band.hpp"
#include "tags/statictext.hpp"
#include "tags/textfield.hpp"

namespace qtreports {

    //All support classes in detail
    namespace detail {

        class Parser;
        using ParseFuncPtr = bool( QXmlStreamReader &, const ObjectPtr & );
        using ParseMethodPtr = bool( Parser::* )( QXmlStreamReader &, const ObjectPtr & );
        using ParseFunc = std::function< ParseFuncPtr >;

        class Parser {

        public:
            Parser();
            ~Parser();

            enum AttributeOption {
                Required, ///< При отсутствии аттрибута будет выдана ошибка.
                Optional ///< При отсутствии аттрибута будет использовано пустое значение.
            };

            /*! \~russian
            Парсит отчет и создает из него внутреннюю структуру данных Report.
            Если во время выполнения произошли ошибки, 
            то функция возвращает false, 
            при этом метод getLastError() возратит описание
            последней произошедшей ошибки.
            @param[in] path Путь к отчету формата .qreport
            @return bool Возвращает true, если функция выполнена успешно.
            */
            bool	            parse( const QString & path );

            /*! \~russian
            Возвращает указатель на внутреннюю структуру отчета.
            Указатель может быть пустый, перед использованием необходимо
            проверить с помощью
            @code
            if ( !report.isNull() ) {
            @endcode
            @return ReportPtr Указатель на внутреннюю структуру отчета.
            */
            const ReportPtr	    getReport() const;

            /*! \~russian
            @return QString Описание последней произошедшей ошибки.
            */
            const QString       getLastError() const;

            /*! \~russian
            Используется для отладки при добавлении новый тэгов.
            @return QString Лог процесса парсинга.
            */
            const QString       getLog() const;

        private:
            ReportPtr	                m_report;
            QString		                m_lastError;
            QTextStream                 m_log;
            QMap< QString, ParseFunc >  m_functions;

            bool    getValue( QXmlStreamReader & reader, QString & data );
            bool    getAttribute( QXmlStreamReader & reader, const QString & name, QString & data, AttributeOption option = AttributeOption::Required );
            bool    goToElementEnd( QXmlStreamReader & reader );
            bool    parseChilds( QXmlStreamReader & reader, const ObjectPtr & object );

            bool    parseDocument( const QString & text );
            bool	parseReport( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseStyle( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseQueryString( QXmlStreamReader & reader, const ReportPtr & report );
            bool	parseField( QXmlStreamReader & reader, const ReportPtr & report );
            bool	parseTitle( QXmlStreamReader & reader, const ReportPtr & report );
            bool	parseDetail( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseBand( QXmlStreamReader & reader, const SectionPtr & section );
            bool    parseStaticText( QXmlStreamReader & reader, const BandPtr & band );
            bool    parseTextField( QXmlStreamReader & reader, const BandPtr & band );
            bool    parseReportElement( QXmlStreamReader & reader, const WidgetPtr & text );
            bool    parseText( QXmlStreamReader & reader, const StaticTextPtr & text );
            bool    parseTextFieldExpression( QXmlStreamReader & reader, const TextFieldPtr & text );

        };

    }
}
#endif // TRANSLATOR_HPP
