#ifndef ARTICLE_H
#define ARTICLE_H

#define MAX_ARTICLE_NAME (128)

struct _article;
typedef struct _article *ArticleP;
typedef struct _article {
    char name[MAX_ARTICLE_NAME];
    int count;
    float price;
    ArticleP next;
} Article;

int initializeArticle(ArticleP article);
ArticleP createArticleFromString(char *str);
int articleToString(char *destination, ArticleP article);
int printArticle(ArticleP article);
ArticleP findArticleByName(ArticleP head, char *name);
int deleteArticleAfter(ArticleP position);
int deleteAllArticles(ArticleP head);
int insertArticleAfter(ArticleP position, ArticleP article);
int insertArticleSorted(ArticleP head, ArticleP article);
#endif