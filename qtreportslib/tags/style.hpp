#pragma once
#ifndef STYLE_HPP
#define STYLE_HPP

#include <QString>
#include <QColor>

namespace qtreports {
    namespace detail {

        class Style {
        public:
            Style();
            Style( int id );

            int		id() const;
            void	setId( int id );

            QString	getName() const;
            void	setName( const QString & name );

            bool	isDefault() const; // Является ли данный стиль стилем по умолчанию
            void	setDefault( bool flag );

            int		fontSize() const; // Размер шрифта
            void	setFontSize( int size );

            QColor	fontColor() const; // Цвет шрифта
            void	setFontColor( const QColor & color );

            QString	fontName() const; // Имя шрифта
            void	setFontName( const QString & name );

            bool	isBold() const; // Жирный шрифт
            void	setBold( bool flag );

            bool	isItalic() const; // Курсив
            void	setItalic( bool flag );

        protected:
            int         m_id;
            bool        m_isDefault;
            bool        m_isBold;
            bool        m_isItalic;
            int         m_fontSize;
            QString     m_name;
            QColor      m_fontColor;
            QString     m_fontName;

        };

    }
}

#endif // STYLE_HPP
